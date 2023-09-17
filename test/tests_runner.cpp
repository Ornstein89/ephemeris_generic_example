#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>

extern "C" {
    #include <SpiceCK.h>
    #include <SpiceUsr.h>
    #include <SpiceZdf.h>
    #include <SpiceZpr.h>
}

#include <ephaccess.h>

TEST(cspice_de440_test, positive)
{
    /* инициализация эфемерид NASA JPL*/
    furnsh_c("naif0012.tls");
    furnsh_c("de440.bsp");
    // furnsh_c("de441_part-1.bsp");
    // furnsh_c("de441_part-2.bsp");

    /* открытие файла с тестовыми данными, сгенерированы через веб-приложение
     * HORIZONS https://ssd.jpl.nasa.gov/horizons/app.html и сохранён в CSV-формате */
    std::ifstream fs;
    //std::ofstream ofs;
    //ofs << std::fixed << std::setprecision(6);
    //ofs.open("cpp_de440_output.txt");
    std::string fname = "horizons_results_Moon_Geocenter_1550_2650_equatorialXYZVxVyVz.txt";
    fs.open(fname);
    ASSERT_TRUE(fs.is_open()) << "test data " << fname << " not found";
    std::string newline;
    while(newline!="$$SOE"){ // пропуск информации в начале файла, переход к координатам
        std::getline(fs, newline);
    }

    /* пример записи из файла:
     * 2688952.500000000 = A.D. 2650-Jan-01 00:00:00.0000 TDB
     *  X = 3.860863166633224E+05 Y =-6.219662313932700E+04 Z =-1.424437947244132E+04
     *  VX= 6.691826275757666E-01 VY= 9.807362685257960E-01 VZ=-1.156771983000147E-01 */
    std::getline(fs, newline);
    int counter = 0;
    while(newline!="$$EOE"){ // "$$EOE" - маркер конца таблицы координат

        /* парсинг строки, считывание даты, координат, скоростей */
        double jd, X_km, Y_km, Z_km, Vx_kms, Vy_kms, Vz_kms;
        std::string tmp, jd_str;

        // ASSERT_TRUE(newline.find("A.D.") != std::string::npos
        //              && newline.find("TDB") != std::string::npos)
        //     << "line \"" << newline << "\" not contain julian day";
        std::stringstream(newline) >> jd_str; // >> jd

        // ASSERT_TRUE(newline.find("X") != std::string::npos
        //              && newline.find("Y") != std::string::npos
        //              && newline.find("Z") != std::string::npos)
        //     << "line \"" << newline << "\" not contain X, Y, Z";

        newline = newline.substr(newline.find(",")+1);
        newline = newline.substr(newline.find(",")+1);
        std::stringstream(newline) >> X_km;
        newline = newline.substr(newline.find(",")+1);
        std::stringstream(newline) >> Y_km;
        newline = newline.substr(newline.find(",")+1);
        std::stringstream(newline) >> Z_km;

        // ASSERT_TRUE(newline.find("VX") != std::string::npos
        //              && newline.find("VY") != std::string::npos
        //              && newline.find("VZ") != std::string::npos)
        //     << "line \"" << newline << "\" not contain VX, VY, VZ";
        newline = newline.substr(newline.find(",")+1);
        std::stringstream(newline) >> Vx_kms;
        newline = newline.substr(newline.find(",")+1);
        std::stringstream(newline) >> Vy_kms;
        newline = newline.substr(newline.find(",")+1);
        std::stringstream(newline) >> Vz_kms;

        SpiceDouble   et_s; //(jd - j2000_c())*spd_c();
        jd_str.resize(jd_str.size()-1);
        str2et_c((jd_str+" JD").c_str(), &et_s); // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/str2et_c.html
        SpiceDouble   state[6] = {0.0};
        SpiceDouble   lt_s;
        spkezr_c("MOON",    // target body name or NAIF ID, https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/naif_ids.html
                 et_s,      // s, seconds past J2000 epoch, https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/time.html
                 "J2000",   // reference frame, https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/frames.html
                 "NONE",
                 "EARTH",   // observer body name or NAIF ID, https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/naif_ids.html
                 state,     // output parameter, body state, wich is [X km, Y km, Z km, Vx km/s, Vy km/s, Vz km/s]
                 &lt_s);    // s, the one-way light time between the observer and target
        // ofs << jd_str << ", " << et_s << ", "
        //     << X_km << ", " << Y_km << ", " << Z_km << ", "
        //     << Vx_kms << ", "<< Vy_kms << ", "<< Vz_kms << ", "
        //     << state[0] << ", " << state[1] << ", " << state[2] << ", "
        //     << state[3] << ", "<< state[4] << ", "<< state[5] << "\n";
        EXPECT_NEAR(X_km, state[0], 100.0); // coordinate tolerance 100 km
        EXPECT_NEAR(Y_km, state[1], 100.0); // coordinate tolerance 100 km
        EXPECT_NEAR(Z_km, state[2], 100.0); // coordinate tolerance 100 km
        EXPECT_NEAR(Vx_kms, state[3], 0.1); // velocity tolerance 0.0005 km/s
        EXPECT_NEAR(Vy_kms, state[4], 0.1); // velocity tolerance 0.0005 km/s
        EXPECT_NEAR(Vz_kms, state[5], 0.1); // velocity tolerance 0.0005 km/s

        std::getline(fs, newline);
    }
    //ofs.close();
    fs.close();
}

TEST(libephaccess_epm2021_test, positive)
{
    // генерация тестовых данных https://iaaras.ru/dept/ephemeris/online/

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

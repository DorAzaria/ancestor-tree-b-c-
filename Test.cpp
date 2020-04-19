#include "doctest.h"
#include "FamilyTree.hpp"
using namespace family;
#include <string>
using namespace std;

//1
TEST_CASE("relations") {
    family::Tree t ("Dor");
        t.addFather("Dor","Ofer")
         .addMother("Dor","Ruth")
         .addFather("Ofer","Gabriel")
         .addMother("Ofer","Naomi")
         .addFather("Ruth","Shlomo")
         .addMother("Ruth","Shushana");

        CHECK(t.relation("Dor") == "me");
        CHECK(t.relation("Do") == "unrelated");
        CHECK(t.relation("D") == "unrelated");
        CHECK(t.relation("DOR") == "unrelated");

        CHECK(t.relation("Ofer") == "father");
        CHECK(t.relation("Ofe") == "unrelated");
        CHECK(t.relation("Of") == "unrelated");
        CHECK(t.relation("O") == "unrelated");
        CHECK(t.relation("OFER") == "unrelated");

        CHECK(t.relation("Ruth") == "mother");
        CHECK(t.relation("Rut") == "unrelated");
        CHECK(t.relation("Ru") == "unrelated");
        CHECK(t.relation("R") == "unrelated");
        CHECK(t.relation("RUTH") == "unrelated");

        CHECK(t.relation("Gabriel") == "grandfather");
        CHECK(t.relation("Gabrie") == "unrelated");
        CHECK(t.relation("Gabri") == "unrelated");
        CHECK(t.relation("Gabr") == "unrelated");
        CHECK(t.relation("Gab") == "unrelated");
        CHECK(t.relation("Ga") == "unrelated");
        CHECK(t.relation("G") == "unrelated");
        CHECK(t.relation("GABRIEL") == "unrelated");

        CHECK(t.relation("Naomi") == "grandmother");
        CHECK(t.relation("Naom") == "unrelated");
        CHECK(t.relation("Nao") == "unrelated");
        CHECK(t.relation("Na") == "unrelated");
        CHECK(t.relation("N") == "unrelated");
        CHECK(t.relation("naomi") == "unrelated");
        CHECK(t.relation("NAOMI") == "unrelated");
        CHECK(t.relation("Na Omi") == "unrelated");

        CHECK(t.relation("Shlomo") == "grandfather");
        CHECK(t.relation("Shlom") == "unrelated");
        CHECK(t.relation("Shlo") == "unrelated");
        CHECK(t.relation("Shl") == "unrelated");
        CHECK(t.relation("Sh") == "unrelated");
        CHECK(t.relation("S") == "unrelated");
        CHECK(t.relation("shlomo") == "unrelated");
        CHECK(t.relation("SHLOMO") == "unrelated");

        CHECK(t.relation("Shushana") == "grandmother");
        CHECK(t.relation("Shushan") == "unrelated");
        CHECK(t.relation("Shusha") == "unrelated");
        CHECK(t.relation("Shush") == "unrelated");
        CHECK(t.relation("Shus") == "unrelated");
        CHECK(t.relation("Shu") == "unrelated");
        CHECK(t.relation("Sh") == "unrelated");
        CHECK(t.relation("S") == "unrelated");
        CHECK(t.relation("suhshana") == "unrelated");
        CHECK(t.relation("SHUSHNA") == "unrelated");
        CHECK(t.relation("SHUshaNA") == "unrelated");

    CHECK_NOTHROW(t.find("greatgreat-grandfather"));
    CHECK_NOTHROW(t.find("grandma"));
    CHECK_NOTHROW(t.find("greatgreat-"));
    CHECK_NOTHROW(t.find("-grandfather"));
    CHECK_NOTHROW(t.find("grandpa-grandfather"));
    CHECK_NOTHROW(t.find("gGRANDpa"));
    CHECK_NOTHROW(t.find("mothera"));
    CHECK_NOTHROW(t.find("motherb"));
    CHECK_NOTHROW(t.find("motherc"));
    CHECK_NOTHROW(t.find("greatgrandfather"));
    CHECK_NOTHROW(t.find("greatgreatgrandfather"));
    CHECK_NOTHROW(t.find("greatgreatgrandmother"));
    CHECK_NOTHROW(t.find("greatgrandmother"));
    CHECK_NOTHROW(t.find("ME"));
    CHECK_NOTHROW(t.find("mE"));
    CHECK_NOTHROW(t.find("Me"));
    CHECK_NOTHROW(t.find("meh"));
    CHECK_NOTHROW(t.find("fater"));
    CHECK_NOTHROW(t.find("mater"));
    CHECK_NOTHROW(t.find("mther"));
}

TEST_CASE("find names") {
    family::Tree d ("Dor");
            d.addFather("Dor","Ofer")
            .addMother("Dor","Ruth")
            .addFather("Ofer","Gabriel")
            .addMother("Ofer","Naomi")
            .addFather("Gabriel","Shaul")
            .addMother("Gabriel","Sarah");

        CHECK(d.find("father")== "Ofer");
        CHECK_NOTHROW(d.find("father"));
        CHECK_NOTHROW(d.find("mother"));
        CHECK_NOTHROW(d.find("grandfather"));
        CHECK_NOTHROW(d.find("grandmother"));
        CHECK(d.find("mother")== "Ruth");
        CHECK(d.find("grandfather")== "Gabriel");
        CHECK(d.find("grandmother")== "Naomi");
        CHECK(d.find("me")== "Dor");
        CHECK(d.find("great-grandmother")== "Sarah");
        CHECK(d.find("great-grandfather")== "Shaul");
        d.remove("Sarah");
        CHECK(d.relation("Sarah")== "unrelated");
        CHECK(d.find("great-grandmother")== "Undefined");
        d.remove("Shaul");
        CHECK(d.relation("Shaul")== "unrelated");
        CHECK(d.find("great-grandfather")== "Undefined");
        d.remove("Ofer");
        CHECK(d.relation("Gabriel")== "unrelated");
        CHECK(d.find("grandfather") == "Undefined");
        CHECK(d.relation("Naomi")== "unrelated");
        CHECK(d.find("grandmother") == "Undefined");

        CHECK(d.find("father") == "Undefined");
        CHECK(d.find("fath") == "Undefined");
        CHECK(d.find("fat") == "Undefined");
        CHECK(d.find("fa") == "Undefined");
        CHECK(d.find("f") == "Undefined");
        CHECK(d.find("FATJER") == "Undefined");
        CHECK(d.find("FATHER") == "Undefined");
        CHECK(d.find("motha") == "Undefined");
        CHECK(d.find("mothe") == "Undefined");
        CHECK(d.find("moth") == "Undefined");
        CHECK(d.find("mot") == "Undefined");
        CHECK(d.find("mo") == "Undefined");
        CHECK(d.find("m") == "Undefined");
        CHECK(d.find("MOTHER") == "Undefined");
        CHECK(d.find("MOTHA") == "Undefined");
        CHECK(d.find("GRANDFATHER") == "Undefined");
        CHECK(d.find("GRANDMOTHER") == "Undefined");
        CHECK(d.find("GREAT-GRANDMOTHER") == "Undefined");
        CHECK(d.find("great-grandmoth") == "Undefined");
        CHECK(d.find("great-grandfath") == "Undefined");
        CHECK(d.find("great") == "Undefined");
        CHECK(d.find("GREAT") == "Undefined");
        CHECK(d.find("Grea") == "Undefined");
        CHECK(d.find("grea") == "Undefined");
        CHECK(d.find("grt") == "Undefined");
        CHECK(d.find("geat") == "Undefined");
        CHECK(d.find("eat") == "Undefined");
        CHECK(d.find("grat") == "Undefined");
        CHECK(d.find("gt") == "Undefined");
        CHECK(d.find("GREat") == "Undefined");
        CHECK(d.find("grandpa") == "Undefined");
        CHECK(d.find("grandma") == "Undefined");
        CHECK(d.find("papa") == "Undefined");
        CHECK(d.find("mama") == "Undefined");
        CHECK(d.find("aunt") == "Undefined");
        CHECK(d.find("grandmotha") == "Undefined");
}
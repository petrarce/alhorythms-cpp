#include <iostream>
#include <absl/strings/str_format.h>
float Hipotenusa(int P /*Perimeter*/, int a /*smaller cater*/)
{

}

float LargerCatet(int P /*Perimeter*/, int a /*smaller cater*/)
{

}

bool IsLargerCatetInt(int P, int a)
{

}

bool IsHipotenusaInt(int P, int a)
{

}

int SolutionCount(int P /*Perimeter*/)
{
    int solCount = 0;
    for(int a = 1; a < P / 2 && a <= LargerCatet(P, a); a++)
    {
        if (!IsLargerCatetInt(P, a) || IsHipotenusaInt(P, a))
            continue;

        solCount++;
        auto h = Hipotenusa(P, a);
        auto b = LargerCatet(P, a);
        std::cout << absl::StrFormat("P(%u) solution: {%i, %f, %f}", P, a, b, h);
    }
    return solCount;
}

int main(int ac, char** av)
{
    int maxP = std::stoi(av[1]);
    std::pair<int, int> PvsSolCnt = {0, 0};
    for (int P = 3; P <= maxP; P++) {

        auto sc = SolutionCount(P);
        PvsSolCnt = std::max(PvsSolCnt, {P, sc}, [](const auto &left, const auto& right) {return left.second > right.second; } );
        std::cout << absl::StrFormat("P(%u) solutions: %i", P, sc);
    }

    std::cout << absl::StrFormat("max solutions: P(%i) : %i", PvsSolCnt.first, PvsSolCnt.second);

    return 0;
}

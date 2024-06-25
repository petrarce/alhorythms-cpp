#include <iostream>
#include <absl/strings/str_format.h>

int main(int ac, char** av)
{
    size_t maxP = std::stoi(av[1]);
    std::pair<size_t, size_t> PvsSolCnt = {0, 0};
    // integer solution are oby available for even P's
    for (size_t P = 2; P <= maxP; P += 2) {

        auto sc = [&](){
            size_t solCount = 0;
            // larger catet of the right triangle
            auto b = [](float P /*Perimeter*/, float a /*smaller cater*/){ return (P * P - 2 * a * P) / (2.f * ( P - a)); };

            for(size_t a = 1; a < P / 2 && a <= b(P, a); a++)
            {
                // since P is even it is enough that a * a is divisible by (P - a)
                // for hipotenuse and larger catet to have an integer value
                if ((a * a) % (P - a) != 0)
                    continue;

                solCount++;
            }
            return solCount;
        }();
        PvsSolCnt = std::max(
            PvsSolCnt,
            {P, sc},
            [](const auto &left,
               const auto& right) { return left.second <= right.second; }
        );
    }

    std::cout << absl::StrFormat("max solutions: P(%i) : %i\n", PvsSolCnt.first, PvsSolCnt.second);

    return 0;
}

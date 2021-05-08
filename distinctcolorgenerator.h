#ifndef UNIQUECOLORGENERATOR_H
#define UNIQUECOLORGENERATOR_H

#include <vector>

class DistinctColorGenerator
{
public:
    /**
     * @brief RGB to Lab color Model, both range is [0,255]
    */
    static std::vector<int> Rgb2Lab(int r, int g, int b);
    static std::vector<std::vector<int>> Rgb2Lab(const std::vector<std::vector<int>>& colors);
    /**
     * @brief RGB to Lab color Model, both range is [0,255]
    */
    static std::vector<int> Lab2Rgb(int l, int a, int b);
    static std::vector<std::vector<int>> Lab2Rgb(const std::vector<std::vector<int>>& colors);


    /**
     * @brief generate giving count distinguishable colors from background colors,
     * default background is white
     * @param rgb color Model, range [0,255]
     * @return rgb color Model, range [0,255]
    */
    static std::vector<std::vector<int>> genUniqueColors(int count,
    std::vector<std::vector<int>> backgroundColors = std::vector<std::vector<int>> {{255, 255, 255}});

private:
    DistinctColorGenerator() = delete;
};

#endif // UNIQUECOLORGENERATOR_H

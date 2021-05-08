#include "distinctcolorgenerator.h"
#include <cmath>
#include <iostream>
#include <algorithm>

std::vector<int> DistinctColorGenerator::Rgb2Lab(int r, int g, int b)
{
    int lab_l = 0.2126007 * r + 0.7151947 * g + 0.0722046 * b;
    int lab_a = 0.3258962 * r - 0.4992596 * g + 0.1733409 * b + 128;
    int lab_b = 0.1218128 * r + 0.3785610 * g - 0.5003738 * b + 128;

    std::vector<int> ret;
    ret.push_back(lab_l);
    ret.push_back(lab_a);
    ret.push_back(lab_b);

    return ret;
}

std::vector<std::vector<int>> DistinctColorGenerator::Rgb2Lab(const std::vector<std::vector<int>>& colors)
{
    std::vector<std::vector<int>> labColors(colors.size());
    for(unsigned int i = 0; i < colors.size(); ++i) {
        labColors[i] = Rgb2Lab(colors[i][0], colors[i][1], colors[i][2]);
    }
    return labColors;
}

std::vector<int> DistinctColorGenerator::Lab2Rgb(int l, int a, int b)
{
    int rgb_r = l + 0.0120308 * a + 0.0021207 * b;
    int rgb_g = l - 0.0035973 * a - 0.0001765 * b;
    int rgb_b = l + 0.0002074 * a - 0.0044965 * b;

    std::vector<int> ret;
    ret.push_back(rgb_r);
    ret.push_back(rgb_g);
    ret.push_back(rgb_b);

    return ret;
}

std::vector<std::vector<int>> DistinctColorGenerator::Lab2Rgb(const std::vector<std::vector<int>>& colors)
{
    std::vector<std::vector<int>> rgbColors(colors.size());
    for(unsigned int i = 0; i < colors.size(); ++i) {
        rgbColors[i] = Lab2Rgb(colors[i][0], colors[i][1], colors[i][2]);
    }
    return rgbColors;
}

std::vector<std::vector<int>> DistinctColorGenerator::genUniqueColors(int count,
                                                              std::vector<std::vector<int>> backgroundColors)
{
    auto n_grid = 17; // choose a factor of 255
    auto n_length = 255 / (n_grid + 1);
    int maxCount = pow(n_grid + 1, 3);
    if(count > maxCount) {
        std::cout << "can't readily distinguish that many colors";
        return std::vector<std::vector<int>>();
    }
    std::vector<std::vector<int>> rgb(maxCount);
    int r = 0, g = 0, b = 0;
    for(int i = 0; i < maxCount; ++i) {
        std::vector<int> aColor = {r, g, b};
        rgb[i] = aColor;

        r += n_length;
        if(r > 255) {
            r = 0;
            g += n_length;
            if(g > 255) {
                g = 0;
                b += n_length;
            }
        }
    }

    auto lab = Rgb2Lab(rgb);
    auto bglab = Rgb2Lab(backgroundColors);

    std::vector<int> mindist2(maxCount, INT_MAX);
    for(unsigned int i = 0; i < bglab.size() - 1; ++i) {
        std::vector<std::vector<int>> dX(maxCount);
        for(int j = 0; j < maxCount; ++j) {
            int l = lab[j][0] - bglab[i][0];
            int a = lab[j][1] - bglab[i][1];
            int b = lab[j][2] - bglab[i][2];
            mindist2[j] = std::min(static_cast<int>(pow(l, 2) + pow(a, 2) + pow(b, 2)), mindist2[j]);
        }
    }

    std::vector<std::vector<int>> colors(count, std::vector<int> {0, 0, 0});
    auto lastlab = bglab.at(bglab.size() - 1);
    for(int i = 0; i < count; ++i) {
        for(int j = 0; j < maxCount; ++j) {
            int l = lab[j][0] - lastlab[0];
            int a = lab[j][1] - lastlab[1];
            int b = lab[j][2] - lastlab[2];
            mindist2[j] = std::min(static_cast<int>(pow(l, 2) + pow(a, 2) + pow(b, 2)), mindist2[j]);
        }
        auto iterator = std::max_element(mindist2.begin(), mindist2.end());
        auto index = std::distance(mindist2.begin(), iterator);
        colors[i] = rgb[index];
        lastlab = lab[index];
    }
    return colors;
}

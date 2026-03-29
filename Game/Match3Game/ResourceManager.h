// ResourceManager.h
#pragma once
#include <graphics.h>
#include <unordered_map>
#include <vector>
#include <random>
#include <algorithm>
class ResourceManager {
public:
    static ResourceManager& getInstance();
    void loadImages(int cellSize);
    IMAGE* getImage(int type);
    void setActiveImages();
private:
    ResourceManager() = default;
    std::unordered_map<int, IMAGE> m_images;
    std::vector<int> activeImages;
public:
    IMAGE bgImage;
    IMAGE buttonImage;
    IMAGE buttonImageDown;
};
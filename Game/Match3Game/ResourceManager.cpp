// ResourceManager.cpp
#include "ResourceManager.h"
#include <cstdio>

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

void ResourceManager::loadImages(int cellSize) {
    for (int i = 1; i <= 19; i++) {
        IMAGE img;
        TCHAR path[64];
        _stprintf_s(path, _T("res/%d.png"), i);
        loadimage(&img, path, cellSize, cellSize);
        m_images[i] = img;
    }
    // ResourceManager.cpp
    loadimage(&buttonImage, _T("res/button.png"), 50, 50);
    loadimage(&buttonImageDown, _T("res/button_down.png"), 50, 50);
    loadimage(&bgImage, _T("res/bg.png"),560,695);
}

IMAGE* ResourceManager::getImage(int type) {
    if (activeImages.empty()) {
        // 第一次使用时初始化
        const_cast<ResourceManager*>(this)->setActiveImages();
    }
    auto it = m_images.find(activeImages[type-1]);
    if (it != m_images.end()) {
        return &(it->second);
    }
    return nullptr;
}
void ResourceManager::setActiveImages()
{
    static std::vector<int> all = []() {
        std::vector<int> v(19);
        for (int i = 1; i <= 19; i++) v[i - 1] = i;
        return v;
        }();

    activeImages = all;  // 直接赋值
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(activeImages.begin(), activeImages.end(), g);
    activeImages.resize(5);  // 只保留前5个
}

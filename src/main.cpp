#include <Geode/Geode.hpp>
#include <Geode/modify/LevelTools.hpp>
#include <filesystem>
using namespace geode::prelude;

static const std::vector<std::string> NAMES = {
    "Magnetic Force",   // 1
    "Rise To Power",    // 2
    "Ice Planet",       // 3
    "Mud Ash",          // 4
    "Meow Super Meow",  // 5
    "Never Stop!",      // 6
    "Carrot",           // 7
    "Neon Horizon"      // 8
};

class $modify(LevelTools) {
    static GJGameLevel* getLevel(int id, bool gauntlet) {
        auto level = LevelTools::getLevel(id, gauntlet);
        if (!level || gauntlet || id < 1 || id > (int)NAMES.size()) return level;

        level->m_levelName = NAMES[id - 1];

        auto path = Mod::get()->getResourcesDir() / fmt::format("level{}.txt", id);
        if (std::filesystem::exists(path)) {
            auto res = utils::file::readString(path);
            if (res) level->m_levelString = res.unwrap();
        }
        return level;
    }
};

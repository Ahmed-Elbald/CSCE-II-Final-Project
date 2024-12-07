#include "settingsmanager.h"

SettingsManager::SettingsManager() {
    // Create new instance of QSettings if it is not already created
    QSettings::setDefaultFormat(QSettings::IniFormat);
    settings = new QSettings();

    // Audio
    settings->setValue("audio/jumpSound" , "qrc:/Assets/audio/man_jumps_1.wav");
    settings->setValue("audio/walkSound" , "qrc:/Assets/audio/man_walks.wav");
    settings->setValue("audio/dieSound" , "qrc:/Assets/audio/male_death_sound.mp3");
    settings->setValue("audio/destroySound" , "qrc:/Assets/audio/shield_hit.m4a");
    settings->setValue("audio/shieldActivationSound" , "qrc:/Assets/audio/shield_active.mp3");
    settings->setValue("audio/wooHooSound" , "qrc:/Assets/audio/woo_hoo.mp3");
    settings->setValue("audio/coinSound" , "qrc:/Assets/audio/coin_pickup.mp3");
    settings->setValue("audio/powerUpSound" , "qrc:/Assets/audio/powerup-sound.mp3");

    settings->setValue("audio/bg/music", "qrc:/Assets/audio/bg_music_1.mp3");
    settings->setValue("audio/startingMenu/music", "qrc:/Assets/audio/starting-menu-music.mp3");
    settings->setValue("audio/startingMenu/clickSound", "qrc:/Assets/audio/button-click-sound.mp3");
    settings->setValue("audio/victorySound", "qrc:/Assets/audio/victory_sound.mp3");
    settings->setValue("audio/levelWinSound", "qrc:/Assets/audio/level_win_sound.mp3");

    settings->setValue("audio/volume", .125);

    // View
    settings->setValue("window/defaultStartOffset", 100);
    settings->setValue("window/defaultEndOffset", 100);
    settings->setValue("window/width", 800);
    settings->setValue("window/height", 600);
    settings->setValue("window/coinsDisplayerXOffset", 40);
    settings->setValue("window/coinsDisplayerYOffset", 0);
    settings->setValue("window/coinsDisplayerFont", "Times");
    settings->setValue("window/coinsDisplayerFontSize", 25);
    settings->setValue("window/coinsDisplayerImage", ":/Assets/images/coin.png");
    settings->setValue("window/lifeDisplayerXOffset", 10);
    settings->setValue("window/lifeDisplayerYOffset", 40);
    settings->setValue("window/lifeDisplayerFullHeartImage", ":/Assets/images/full_heart.png");
    settings->setValue("window/lifeDisplayerHalfHeartImage", ":/Assets/images/half_heart.png");
    settings->setValue("window/lifeDisplayerEmptyHeartImage", ":/Assets/images/empty_heart.png");


    // Scene
    settings->setValue("scene/defaultHeight", 600);
    settings->setValue("scene/endFlag", ":/Assets/images/end_flag.png");

    // Images
    settings->setValue("spikes/1", ":/Assets/images/Spikes/1.png");
    settings->setValue("spikes/2", ":/Assets/images/Spikes/2.png");
    settings->setValue("blocks/1", ":/Assets/images/Blocks/1.png");
    settings->setValue("blocks/2", ":/Assets/images/Blocks/2.png");
    settings->setValue("blocks/3", ":/Assets/images/Blocks/3.png");
    settings->setValue("blocks/4", ":/Assets/images/Blocks/4.png");
    settings->setValue("blocks/5", ":/Assets/images/Blocks/5.png");
    settings->setValue("blocks/6", ":/Assets/images/Blocks/6.png");

    // Levels (Scene width, ground level, player lives, background path)
    settings->setValue("levels/1/sceneWidth", 3000);
    settings->setValue("levels/1/groundLevel", 0.88);
    settings->setValue("levels/1/playerLives", 5);
    settings->setValue("levels/1/backgroundPath", ":/Assets/images/bg_1.jpg");
    settings->setValue("levels/2/sceneWidth", 5000);
    settings->setValue("levels/2/groundLevel", 0.87);
    settings->setValue("levels/2/playerLives", 5);
    settings->setValue("levels/2/backgroundPath", ":/Assets/images/bg_2.jpg");
    settings->setValue("levels/3/sceneWidth", 7000);
    settings->setValue("levels/3/groundLevel", 0.787);
    settings->setValue("levels/3/playerLives", 4);
    settings->setValue("levels/3/backgroundPath", ":/Assets/images/bg_3.jpg");
    settings->setValue("levels/4/sceneWidth", 7000);
    settings->setValue("levels/4/groundLevel", 0.67);
    settings->setValue("levels/4/playerLives", 3);
    settings->setValue("levels/4/backgroundPath", ":/Assets/images/bg_4.jpg");
    settings->setValue("levels/5/sceneWidth", 8000);
    settings->setValue("levels/5/groundLevel", 0.74);
    settings->setValue("levels/5/playerLives", 2);
    settings->setValue("levels/5/backgroundPath", ":/Assets/images/bg_5.jpg");


    // Player
    settings->setValue("player/walkSpeed", 3);
    settings->setValue("player/runSpeed", 5);
    settings->setValue("player/jumpSpeed", -10.75);
    settings->setValue("player/gravity", 0.375);
    settings->setValue("player/spriteFrameWidth", 128);
    settings->setValue("player/spriteFrameHeight", 128);
    settings->setValue("player/spriteContentOffsetX", 45);
    settings->setValue("player/spriteContentOffsetY", 45);
    settings->setValue("player/spriteContentWidth", 38);
    settings->setValue("player/spriteContentHeight", 83);
    settings->setValue("player/walkTimerInterval", 16);
    settings->setValue("player/jumpTimerInterval", 16);
    settings->setValue("player/fallTimerInterval", 16);
    settings->setValue("player/collisionTimerInterval", 16);
  
    // Coin
    settings->setValue("coin/spriteSheet/1", ":/Assets/images/Coins/coin1.png");
    settings->setValue("coin/spriteSheet/2", ":/Assets/images/Coins/coin2.png");
    settings->setValue("coin/spriteWidth", 180);
    settings->setValue("coin/spriteHeight", 20);

    // Coin sprite properties
    settings->setValue("coin/spriteFrameWidth", 20);
    settings->setValue("coin/spriteFrameHeight", 20);
    settings->setValue("coin/spriteContentOffsetX", 0);
    settings->setValue("coin/spriteContentOffsetY", 0);
    settings->setValue("coin/spriteContentWidth", 20);
    settings->setValue("coin/spriteContentHeight", 20);
    settings->setValue("coin/volume", 0.2);
    settings->setValue("audio/coinPickUp/1", "qrc:/Assets/audio/capture_coin.wav");
    settings->setValue("audio/coinPickUp/2" , "qrc:/Assets/audio/coin_pickup.mp3");
    settings->setValue("audio/coinPickUp/3" , "qrc:/Assets/audio/coin_pickup_2.mp3");
    settings->setValue("coin/scale", 2);

    // Enemy
    settings->setValue("enemy/spriteSheetPath", ":/Assets/images/NightBorne/NightBorne.png");
    settings->setValue("enemy/spriteWidth", 1840);
    settings->setValue("enemy/spriteHeight", 400);
    settings->setValue("enemy/spriteFrameWidth", 80);
    settings->setValue("enemy/spriteFrameHeight", 80);
    settings->setValue("enemy/spriteContentOffsetX", 0);
    settings->setValue("enemy/spriteContentOffsetY", 0);
    settings->setValue("enemy/spriteContentWidth", 80);
    settings->setValue("enemy/spriteContentHeight", 80);
    settings->setValue("enemy/spriteSheet/idle", 9*80); // 9 frames
    settings->setValue("enemy/spriteSheet/walk", 6*80); // 6 frames
    settings->setValue("enemy/spriteSheet/beaten", 5*80); // 5 frames
    settings->setValue("enemy/spriteSheet/fight", 6*80); // 6 frames
    settings->setValue("enemy/spriteSheet/die", 23*80); // 23 frames
    settings->setValue("enemy/scale", 2);

    // Order in Spritesheet (0 based)
    settings->setValue("enemy/spriteSheet/idle/order", 0);
    settings->setValue("enemy/spriteSheet/walk/order", 1);
    settings->setValue("enemy/spriteSheet/fight/order", 2);
    settings->setValue("enemy/spriteSheet/beaten/order", 3);
    settings->setValue("enemy/spriteSheet/die/order", 4);

    // Enemy speed
    settings->setValue("enemy/walkSpeed", 4);
    settings->setValue("enemy/walkRange", 400);
    settings->setValue("enemy/fightRange", 50);
    settings->setValue("enemy/checkPlayerInterval", 50);
    settings->setValue("enemy/walkTimerInterval", 25);
    settings->setValue("enemy/startX", 800);

    // Sprites
    settings->setValue("spriteUpdateInterval", 75);



    // Obstacles
    settings->setValue("blocks/startX", 800);
    settings->setValue("blocks/height", 48);
    settings->setValue("blocks/width", 48);
    settings->setValue("blocks/distanceFromGround",100);
    settings->setValue("blocks/collectionNumber", 10);
    settings->setValue("blocks/collectionDistance", 150);
    settings->setValue("blocks/scale", 1);
    settings->setValue("blocks/numberOfCollections", 25);
    settings->setValue("levelEndOffset", 200);


    // Ratios
    settings->setValue("ratios/coin", 4);
    settings->setValue("ratios/healthPotion", 50);
    settings->setValue("pickUps/height", 100);
    settings->setValue("spikes/scale", 4);
    settings->setValue("ratios/enemy", 100);

    // Potions
    settings->setValue("potion/health/path", ":/Assets/images/Health.png");
    settings->setValue("potion/health/scale", 1.5);
}

SettingsManager::~SettingsManager() {
    // Delete the settings object
    delete settings;
}

SettingsManager SM = SettingsManager();


#ifndef PARAM_H
#define PARAM_H
// 头文件

/*
 * 此文件包含了游戏中所有宏定义的参数
 */

// 窗口参数
#define WIDTH_OF_WINDOW 1280 // 窗口宽度
#define HEIGHT_OF_WINDOW 720 // 窗口高度

// 菜单参数
#define WIDTH_OF_BAR    1280// 菜单的长度
#define HEIGHT_OF_BAR   130// 菜单的高度

// 游戏控制参数
#define REFRESH_TIME 50 // 刷新时间
#define EAT_FOOD_DISTANCE 15 // 吃到食物的距离
#define PREGNANT_TIME 15000 // 古比妈咪怀孕时间

// 种类ID
#define TYPE_GUPPI 1
#define TYPE_ALIEN 2
#define TYPE_MONEY 3
#define TYPE_FOOD 4
#define TYPE_SNAIL 5
#define TYPE_BREEDER 6
#define TYPE_PREDATOR 7
#define TYPE_BIGPREDATOR 8

// 鱼类参数
#define HUNGRY_VALUE 0
#define DIE_VALUE  -100
#define FISH_WIDTH 80
#define FISH_HEIGHT 80
#define CREATE_MONEY_TIME 100
#define GUPPI_MONEY 25
#define GUPPI_GROW_SPEED 10
#define GUPPI_GROW_TIME 100
#define GUPPI_GROW_TO_MIDDLE 300
#define GUPPI_GROW_TO_BIG 800
#define GUPPI_GROW_TO_KING 1500
#define GUPPI_GROW_STAGE_SMALL 0
#define GUPPI_GROW_STAGE_MIDDLE 1
#define GUPPI_GROW_STAGE_BIG 2
#define GUPPI_GROW_STAGE_KING 3
#define GAP_X_LOCK_LEFT_FOOD 20
#define GAP_X_LOCK_RIGHT_FOOD -45
#define GAP_Y_LOCK_FOOD 15
#define GAP_X_LOCK_LEFT_FISH 36
#define GAP_X_LOCK_RIGHT_FISH -60
#define GAP_Y_LOCK_FISH 35
#define GET_FOOD_VALUE 30
#define BREEDER_GROW_TO_MIDDLE 300
#define BREEDER_GROW_TO_BIG 900
#define BREEDER_GROW_STAGE_SMALL 0
#define BREEDER_GROW_STAGE_MIDDLE 1
#define BREEDER_GROW_STAGE_BIG 2
#define BREEDER_CREATE_FISH_SMALL 10000000
#define BREEDER_CREATE_FISH_MIDDLE 300
#define BREEDER_CREATE_FISH_BIG 150
#define BIGPREDATOR_SIZE 160
#define FISH_MOVE_TIME 10
#define FISH_LAST_TIME 50

// 食物参数
#define FOOD_WIDTH 40
#define FOOD_HEIGHT 40
#define FOOD_NUM_SIZE 40
#define FOOD_NUM_COST 300
#define FOOD_LEVEL_COST 200

// 金钱参数
#define MONEY_SIZE 72
#define MONEY_VALUE_ONE 15
#define MONEY_VALUE_TWO 35
#define MONEY_VALUE_THREE 100
#define MONEY_VALUE_FOUR 100
#define MONEY_VALUE_FIVE 200
#define MONEY_VALUE_SIX 2000
#define PRICE_EGG       3000
#define PRICE_GUPPI     100
#define PRICE_BREEDER   200
#define PRICE_PREDATOR  1000
#define PRICE_BIGPREDATOR 10000

// 鸡蛋参数
#define EGG_WIDTH   46
#define EGG_HEIGHT 39

// 外星人参数
#define ALIEN_REFRESH_TIME 80000
#define ALIEN_SIZE 160
#define BLUE_ALIEN_ID 0
#define RED_ALIEN_ID 1
#define GUS_ALIEN_ID 2
#define BLUE_ALIEN_LIFE 100
#define RED_ALIEN_LIFE 200
#define GUS_ALIEN_LIFE 150

// 宠物参数
#define GUPPI_MUMMY_SIZE 80
#define SNAIL_SIZE  80

// 图片路径
#define IMAGE_LOADING   ":/images/loading"
#define IMAGE_MENU      ":/images/menu"
#define IMAGE_BACKGROUND    ":/images/bg"
#define IMAGE_ICON      ":/images/icon"
#define IMAGE_GUPPI ":/images/Images/guppi.png"
#define IMAGE_GUPPI_HUNGRY ":/images/Images/hungryswim.png"
#define IMAGE_GUPPI_DIE ":/images/Images/smalldie.png"
#define IMAGE_BAR   ":/images/bar"
#define IMAGE_GUPPI_ICON ":/images/guppi_icon"
#define IMAGE_FOOD ":/images/Images/food.png"
#define IMAGE_MONEY ":/images/Images/money.png"
#define IMAGE_BLUE_ALIEN ":/images/Images/blue_alien.png"
#define IMAGE_RED_ALIEN ":/images/Images/red_alien.png"
#define IMAGE_GUPPI_MUMMY ":/images/Images/guppi_mummy.png"
#define IMAGE_GUPPI_MUMMY_P ":/images/Images/guppi_mummy_pregnant.png"
#define IMAGE_SNAIL ":/images/Images/snail.png"
#define IMAGE_SNAIL_HIDE    ":/images/Images/snail_hide.png"
#define IMAGE_BREEDER ":/images/Images/breeder.png"
#define IMAGE_HUNGRY_BREEDER ":/images/Images/hungrybreeder.png"
#define IMAGE_DIE_BREEDER ":/images/Images/diebreeder.png"
#define IMAGE_BREEDER_ICON ":/images/breeder_icon"
#define IMAGE_PREDATOR ":/images/Images/predator.png"
#define IMAGE_HUNGRY_PREDATOR ":/images/Images/hungrypredator.png"
#define IMAGE_DIE_PREDATOR ":/images/Images/diepredator.png"
#define IMAGE_PREDATOR_ICON ":/images/predator_icon"
#define IMAGE_BIGPREDATOR ":/images/Images/bigpredator.png"
#define IMAGE_DIE_BIGPREDATOR   ":/images/Images/diebigpredator.png"
#define IMAGE_BIGPREDATOR_ICON  ":/images/bigpredator_icon"
#define IMAGE_EGG   ":/images/Images/EggPieces.gif"
#define IMAGE_HATCH_SCREEN ":/images/Images/hatchscreen.png"
#define IMAGE_GUS ":/images/Images/gus.png"
#define IMAGE_LEVEL ":/images/Images/level.png"
#define IMAGE_FOOD_ICON ":/images/Images/foodicon.gif"
#define IMAGE_DEFEAT    ":/images/Images/defeat.png"
#define IMAGE_SECOND_HATCH_SCREEN ":/images/Images/hatchscreen2.png"
#define IMAGE_VICTORY ":/images/Images/victory.png"

// 音乐路径
#define SOUND_BACKGROUND_MUSIC ":/music/sound/Insaniq2.mo3(2).wav"
#define SOUND_BUY ":/music/sound/buy.wav"
#define SOUND_DIE ":/music/sound/die.wav"
#define SOUND_DROP ":/music/sound/drop.wav"
#define SOUND_MONEY ":/music/sound/money.wav"
#define SOUND_PUNCH ":/music/sound/punch.wav"
#define SOUND_SHORTOFMONEY ":/music/sound/shortofmoney.wav"
#define SOUND_WARNNING ":/music/sound/warnning.wav"
#define SOUND_EAT ":/music/sound/eat.wav"

// 场景ID
#define SCENE_BEGIN_MENU            1001
#define SCENE_HELP                  1002
#define SCENE_PAUSE                 1003
#define SCENE_LOADING               1004
#define SCENE_GAME_ONE              1005
#define SCENE_HATCH_SCREEN          1006
#define SCENE_GAME_TWO              1007
#define SCENE_SECOND_HATCH_SCREEN   1008
#define SCENE_GAME_THREE            1009
#define SCENE_VICTORY               1010
#define SCENE_DEFEAT                1011

#endif // PARAM_H

#define BEETLE 4
#define FLOWER 3
#define WALL 2
#define NOTHING 1

#define G_WIDTH_MAX 50 
#define G_WIDTH_MIN 5
#define G_HEIGHT_MAX 50
#define G_HEIGHT_MIN 5

#define MAXTIME 100

#define NUM_ACTIONS 5

#define A_STEP 0
#define A_ROTATERIGHT 1
#define A_ROTATELEFT 2
#define A_WAIT 3
#define A_COPULATE 4 //A_COPULATE must be the last action

#define A_STEP_COSTS 2

#define NOT_HUNGRY 1
#define HUNGRY 0
#define DEAD -1

#define WEST 0
#define NORTH 1
#define EAST 2
#define SOUTH 3

//beetle's limits on features
#define MAX_ENERGY 50
#define MAX_LEARN_ABILITY 50
#define MAX_AGE 50
//dimesions of beetles brain
#define BRAIN_D1 2
#define BRAIN_D2 4
#define BRAIN_D3 4
#define BRAIN_D4 4

//dimesions of beetles expectations on partner
#define EXPECT_ON_PARTNER_D1 4 
#define EXPECT_ON_PARTNER_D2 2

#define EXPECT_ON_PARTNER_MAX_1 50
#define EXPECT_ON_PARTNER_MAX_2 50
#define EXPECT_ON_PARTNER_MAX_3 50
#define EXPECT_ON_PARTNER_MAX_4 50

//0.Energy, 1.Age, 2.InvInChild, 3.LearningAbility
#define EXPECT_ENERGY 0
#define EXPECT_AGE 1
#define EXPECT_INVINCHILD 2
#define EXPECT_LEARNABILITY 3

#define NUMOPTVARIABLES 1

#define MAP_BMP_FILE L"env_cfg.bmp"

//colors of the map of the environment
#define CFG_CLR_FLOWER_BOTTOM   RGB(0,0,0)  //= NOTHING
#define CFG_CLR_FLOWER_TOP		RGB(0,255,0)
#define CFG_CLR_BEETLE			RGB(255,255,255)
#define CFG_CLR_WALL			RGB(255,0,0)

//console interface
#define QUIT_CHAR 'x'
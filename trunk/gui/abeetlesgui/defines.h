#define INVALID_NUM -1

//possible contents of a cell of the environment
#define BEETLE 4
#define FLOWER 3
#define WALL 2
#define NOTHING 1

#define G_WIDTH_MAX 50 
#define G_WIDTH_MIN 5
#define G_HEIGHT_MAX 50
#define G_HEIGHT_MIN 5
#define DEFAULT_GRID_WIDTH 30
#define DEFAULT_GRID_HEIGHT 30

#define EFF_BMP_X 100
#define EFF_BMP_Y 20
#define EFF_BMP_FILE "EnergyFromFlower.bmp"

#define MAXTIME 200000 

#define NUM_ACTIONS 3	//changed 26.5. - beforehead: 5, including A_COPULATE

#define A_STEP 0
#define A_ROTATERIGHT 1
#define A_ROTATELEFT 2

//26.5.2007 - A_WAIT omitted - it gets beetles into deadlock situation. They should never decide for waiting, when they are hungry. And when when they are not hungry, it might be useful only as waiting for somebody to come and make child with him. But even in this situation it is not clever - beetle cannot finish it, because it has no memory. So it waits until it gets hungry or situation around changes.
//#define A_WAIT 3
//26.5.2007 - A_COPULATE omited from actions that can a beetle decide for. It is compulsory action in case a beetle sees another beetle in front of him.
//#define A_COPULATE 4 //A_COPULATE must be the last action

#define HA_COPULATE 3	//hardwired action - copulate

//!!!remake to const attributes of CEnvironment
#define A_STEP_COSTS 2
#define A_ROTATION_COSTS 2
#define A_COPULATION_COSTS 3
#define A_WAIT_COSTS 1 //used when chosen action cannot be performed


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
#define MAX_AGE 100
#define MAX_INV_IN_CHILD 25
#define MAX_HIST 100

//dimesions of beetles brain
#define BRAIN_D1 2
#define BRAIN_D2 4
#define BRAIN_D3 4
#define BRAIN_D4 4

//dimesions of beetles expectations on partner
#define EXPECT_ON_PARTNER_D 6 

//probability of mutation
#define MUTATION_PROB 2
#define LEARN_PROB 2

//not used any more
/*#define EXPECT_ON_PARTNER_MAX_1 50
#define EXPECT_ON_PARTNER_MAX_2 50
#define EXPECT_ON_PARTNER_MAX_3 50
#define EXPECT_ON_PARTNER_MAX_4 50

//0.Energy, 1.Age, 2.InvInChild, 3.LearningAbility
#define EXPECT_ENERGY 0
#define EXPECT_AGE 1
#define EXPECT_INVINCHILD 2
#define EXPECT_LEARNABILITY 3*/

#define NUMOPTVARIABLES 1

#define MAP_BMP_FILE "env_cfg.bmp"
#define DEFAULT_FILE_NAME "default"

//colors of the map of the environment
#define CFG_CLR_FLOWER_BOTTOM   0	//= NOTHING
#define CFG_CLR_FLOWER_TOP		255
#define CFG_CLR_BEETLE			QColor(255,255,255)
#define CFG_CLR_WALL			QColor(255,0,0)

//console interface
#define QUIT_CHAR 'x'
#define SAVE_CHAR 's'

//boundaries of types
#define MAX_INT 2147483647

//statistics concerned:
#define BUF_SIZE 500
#define STAT_AGR_FILE "statAgr.txt"
#define STAT_TIME_FILE "statTime.csv"
#define STAT_TIME_FILE_OLD "statTime_old.csv"

//GUI concerned:
#define NUM_ZOOM 5
#define START_ZOOM_VALUE 2

#define NUM_TYPE_VIEW 6
#define TYPE_VIEW_1 "normal"
#define TYPE_VIEW_2 "age"
#define TYPE_VIEW_3 "energy"
#define TYPE_VIEW_4 "fertility"
#define TYPE_VIEW_5 "hunger"
#define TYPE_VIEW_6 "growth of flowers"

#define TIME_STEP 15	//in miliseconds - the time between two time slices.
#define COLOR_NOTHING "white"
#define COLOR_WALL	"black"
#define COLOR_FLOWER "yellow"

#define EMPTY_FIELD_SIZE 200



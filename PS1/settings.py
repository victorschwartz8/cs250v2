# ======= GENERAL SETTINGS: Adapt these per assignment =============
ASSIGNMENT = "Duke ECE/CS 250 Homework 1"
SEMESTER = "Spring 2018"
TEST_DIR = 'tests' # where test files are located
IS_GRADER = True # if true, we'll expect to see a 'points' parameter in test setup

SPIM_BINARY = 'spim' # location of spim executable (or just 'spim' if in path); only needed if mode is SPIM
LOGISIM_JAR = 'logisim_cli.jar' # location of logisim_cli.jar; only needed if mode is LOGISIM

# modes: 
#   EXECUTABLE - for C programs, etc.
#   SPIM       - run with command line spim
#   LOGISIM    - run with logisim command-line front-end
MODE = 'EXECUTABLE'

NON_ZERO_EXIT_STATUS_PENALTY = 0.75 # multiply score by this if exit status is non-zero
VALGRIND_PENALTY = 0.5 # multiply score by this if a valgrind test showed a leak

# ============= TEST SETUP ========================
suite_names = ('bytwoorthree', 'recurse', 'PlayerStats' )
suites = {
    "bytwoorthree": [
        { "desc": "n = 1",  "args": ['1'],  'valgrind': True},
        { "desc": "n = 2",  "args": ['3'],  'valgrind': True},
        { "desc": "n = 3",  "args": ['5'],  'valgrind': True},
        { "desc": "n = 4",  "args": ['10'],  'valgrind': True},
    ],
    "recurse": [
        { "desc": "n = 1",  "args": ['1'],   'valgrind': True},
        { "desc": "n = 2",  "args": ['2'],   'valgrind': True},
        { "desc": "n = 3",  "args": ['3'],   'valgrind': True},
        { "desc": "n = 4",  "args": ['4'],   'valgrind': True},
    ],
    "PlayerStats": [
        { "desc": "One Player",                     "args": [TEST_DIR+'/PlayerStats_input_0.txt'], 'diff': hoopstat_diff, 'valgrind':True},
        { "desc": "Two players with same stats",          "args": [TEST_DIR+'/PlayerStats_input_1.txt'], 'diff': hoopstat_diff, 'valgrind':True},
        { "desc": "Two players with different stats",      "args": [TEST_DIR+'/PlayerStats_input_2.txt'], 'diff': hoopstat_diff, 'valgrind':True},
        { "desc": "Ten players",                    "args": [TEST_DIR+'/PlayerStats_input_3.txt'], 'diff': hoopstat_diff, 'valgrind':True},
        { "desc": "Don't print after DONE",        "args": [TEST_DIR+'/PlayerStats_input_4.txt'], 'diff': hoopstat_diff, 'valgrind':True},
        { "desc": "Correct output with play minutes equal to zero",    "args": [TEST_DIR+'/PlayerStats_input_5.txt'], 'diff': hoopstat_diff, 'valgrind':True},
        { "desc": "Correct output with both points and assistances equal to zero",       "args": [TEST_DIR+'/PlayerStats_input_6.txt'], 'diff': hoopstat_diff, 'valgrind':True},
        { "desc": "100 players, some stats are zero",                    "args": [TEST_DIR+'/PlayerStats_input_7.txt'], 'diff': hoopstat_diff, 'valgrind':True},
        { "desc": "Correct output on empty file",  "args": [TEST_DIR+'/PlayerStats_input_8.txt'], 'diff': hoopstat_diff, 'valgrind':True},
    ]    
}

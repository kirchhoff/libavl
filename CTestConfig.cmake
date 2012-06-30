set(CTEST_NIGHTLY_START_TIME "02:00:00 GMT+1")

set(MODEL "Weekly")
set(CTEST_PROJECT_NAME "LibAvl")
set(CTEST_DROP_SITE "yapbreak.fr")
set(CTEST_DROP_LOCATION "/CDash/submit.php?project=LibAvl")
set(CTEST_DROP_SITE_CDASH TRUE)

set(MEMORYCHECK_COMMAND "/usr/bin/valgrind")
set(MEMORYCHECK_COMMAND_OPTIONS "-q --trace-children=yes --smc-check=all --read-var-info=yes --leak-check=full --show-reachable=yes --track-origins=yes --malloc-fill=ff --free-fill=42")

set(UPDATE_COMMAND "git")

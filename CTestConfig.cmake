#       DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
#                   Version 2, December 2004 
#
# Copyright (C) 2013 Adrien Oliva <adrien.oliva@yapbreak.fr>
#
# Everyone is permitted to copy and distribute verbatim or modified 
# copies of this license document, and changing it is allowed as long 
# as the name is changed. 
#
#           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
#  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 
#
# 0. You just DO WHAT THE FUCK YOU WANT TO.
set(CTEST_NIGHTLY_START_TIME "02:00:00 GMT+1")

set(MODEL "Weekly")
set(CTEST_PROJECT_NAME "LibAvl")
set(CTEST_DROP_SITE "cdash.yapbreak.fr")
set(CTEST_DROP_LOCATION "/submit.php?project=libavl")
set(CTEST_DROP_SITE_CDASH TRUE)

set(MEMORYCHECK_COMMAND "/usr/bin/valgrind")
set(MEMORYCHECK_COMMAND_OPTIONS "-q --trace-children=yes --smc-check=all --read-var-info=yes --leak-check=full --show-reachable=yes --track-origins=yes --malloc-fill=ff --free-fill=42")

set(UPDATE_COMMAND "git")

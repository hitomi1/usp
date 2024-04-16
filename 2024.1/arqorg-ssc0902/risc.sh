#!/bin/bash
if [ $# -eq 1 ]; then

    java -jar rars1_5.jar "$1"

else

    java -jar rars1_5.jar

fi

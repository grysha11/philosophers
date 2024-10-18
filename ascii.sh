#!/bin/bash

BLUE="\033[0;94m"
RED="\033[0;91m"
GREEN="\033[0;92m"
YELLOW="\e[0;33m"
CYAN="\033[0;96m"
COLOR="\033[0m"

if [ $# -eq 0 ]; then
    exit 1
fi

ARG=$1

if [ "$ARG" == "1" ]; then
    echo -e "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⠤⢤⣄⣤⠶⠖⠒⠶⠶⠶⠶⠛⠛⠲⠶⠾⡏⠋⠉⣯⡛⢉⡉⠉⠛⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⢻⡀⠀⠀⣠⠛⠛⢦⡀⠀⢠⣄⠀⢻⣆⣺⠂⠘⠳⡦⠛⠓⠿⣄⢺⣷⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣀⡤⠶⠋⢀⠀⠈⠳⣄⠀⢻⡀⠀⢀⡇⠀⠀⢙⡟⠁⠀⠈⠙⢦⡞⠀⠀⠀⠀⠈⢣⡉⠁⢳⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⢀⣴⠋⠀⢠⠖⠉⠙⣆⠀⠈⢳⡄⠉⠛⠉⠀⠀⠀⣾⠀⠀⠀⠀⠀⠀⠹⡄⠀⠀⠀⠀⠀⢳⡀⠀⢳⡤⠤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⣤⠶⠋⠀⠀⠀⡏⠀⠀⠀⣿⠀⠀⠀⢷⠲⣋⡷⠀⠀⠀⢿⠀⠀⠀⠀⠀⠀⠀⠹⡄⠀⠀⠀⠀⠀⡇⣰⠋⠀⢀⣽⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⢿⣆⡄⠀⠀⠀⠳⣄⣠⠞⠁⠀⠀⠀⠈⢧⡀⠀⠀⠀⠀⠘⡆⠀⠀⠀⠀⠀⣀⣀⣿⠴⠦⣄⠀⣠⠟⠁⠀⢀⡾⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣀⠀
⠀⠙⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⠀⠀⠀⠀⠀⣹⡦⢤⡀⠀⢸⣷⣦⣿⣼⣷⣼⠗⠁⠀⢀⡴⠟⡏⠀⠀⠀⠀⠀⠀⠀⢀⣤⠤⣤⣤⣤⡾⢁⡟⠀
⠀⠀⠈⣧⠀⠀⠀⢀⣤⢤⠀⠀⠀⢀⡀⠀⠸⡄⠀⠀⣰⣟⣻⣟⠀⢹⣄⠘⣝⣿⠏⠹⠟⢁⣀⡤⣖⡋⠁⠀⡇⠀⠀⠀⠀⢀⡤⠖⠛⠤⢾⣥⠤⠼⣧⡾⠁⠀
⠀⠀⠀⠈⢷⡀⠀⢸⠁⣼⠀⢀⡔⠉⠙⡆⠀⠻⡄⠀⢿⡉⠸⢿⣦⡀⠉⠉⠋⠁⠀⠀⠀⠉⠉⢀⣠⣭⠗⠒⢹⡄⠀⢀⡴⠋⠈⠁⠚⠀⠀⢉⡓⠒⠈⠹⣆⠀
⠀⠀⠀⠀⠀⠻⡄⠈⠛⠁⠀⡏⠀⠀⢠⡇⠀⠀⢱⠀⠀⠉⠀⠀⣿⣿⣷⣶⣶⡶⠶⠶⣶⡞⠋⠉⢧⠀⠀⠀⠈⢳⠀⢼⠁⠄⠉⠁⡄⠘⠋⠈⠀⠀⢀⣠⣾⡄
⠀⠀⠀⠀⠀⠀⢷⡀⠀⠀⠘⣇⣀⡠⠟⠀⠀⠀⢸⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣷⠀⣀⣸⣷⣦⣴⠞⠂⠀⠀⠀⡿⢸⡿⢽⣳⣶⣤⣴⣶⣶⣖⡶⠿⢿⡞⢹⡇
⠀⠀⠀⠀⠀⠀⠀⠹⣤⠀⠀⠈⠉⠀⠀⠀⠀⠀⠀⢷⡀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⡴⠲⡄⢿⠈⢧⣀⣓⣶⣯⣿⣶⣴⣆⣘⡦⠼⠷⣿⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢿⡀⠀⢀⣠⣄⠀⠀⠀⠀⠀⠀⣷⣀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⢣⣀⡇⢸⠆⠀⢻⣍⠉⠉⠉⠉⠉⢉⣁⣠⣤⠶⠋⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠈⢷⡀⢿⣠⠏⠀⠀⠀⠀⠀⠘⡏⣰⠶⡄⠀⠀⠹⡟⠛⠛⠻⡍⠉⠙⠛⣿⣿⣀⠀⣉⢁⣾⠞⠙⣆⠈⠉⣹⠋⣹⠋⠉⠁⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣇⠀⠀⠀⢠⠖⠲⣄⠀⠀⢻⡌⢛⣳⣤⡀⠀⠹⣄⠀⠀⠀⠀⠀⠀⣸⣿⠟⠈⣿⡋⣿⢰⡗⠛⢉⣉⣁⡴⠃⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠿⡀⠀⠀⡟⠀⠀⢹⡄⠀⠀⣿⢾⡁⠀⢹⠀⠀⢈⡛⠢⠤⢤⣤⣾⣻⡥⢾⡵⠛⠛⣿⣈⣻⡟⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡀⢸⡇⠀⠀⠀⢧⠀⠀⢿⠈⠓⠶⢋⣀⣀⣀⡽⠷⠒⣾⠋⢙⣷⣤⠊⠀⠀⣠⣧⠈⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢹⢻⡀⠀⠀⠀⢸⠋⠙⢺⡗⠒⠋⠉⠛⠒⠦⣤⣤⡞⢹⡖⢿⡤⠵⢒⣾⣭⡽⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠦⣬⣿⢻⡋⠉⠀⠀⠰⡇⠀⠀⠀⣀⣤⡤⠴⢟⣫⡟⠀⠘⣿⡿⠟⠟⠋⠁⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⢸⡟⢸⣯⣭⣓⠲⠶⡷⢒⣋⣽⣷⡆⠸⡿⠟⠛⢦⣀⡼⠁⠀⣀⣠⡴⠾⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡄⠀⡇⢸⠉⠉⠛⠀⠀⡇⠿⠛⠉⠀⠀⠀⠀⢀⣠⣤⠿⠗⠛⠋⣯⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠓⠲⡇⠘⢧⣄⣀⣀⠀⡇⢀⣀⣠⡤⠴⠒⠛⠉⢹⣇⣀⣀⣀⣠⠿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⠁⠀⠀⢻⣽⠉⠙⠛⠉⠉⠀⣧⠀⠀⠀⠀⠀⠉⡏⢹⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⣀⠀⠀⡟⣾⠧⣤⣤⣤⠶⠚⠁⠀⠀⠀⠀⠀⢸⣇⣼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣧⣏⢸⠀⣿⠉⠀⣿⢀⡇⠀⠀⠀⠀⠀⠀⠀⠀⢸⣷⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠛⠻⠋⠀⢀⣿⣸⡇⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣾⡇⠀⠀⠀⠀⠀⠀⠀⣴⣿⣶⣿⣷⣤⣴⣶⣶⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡇⠘⣧⠀⠀⠀⢀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⣷⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣾⣟⣹⣿⡆⠀⠈⠉⠉⠉⠀⠉⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${COLOR}"
fi

if [ "$ARG" == 2 ]; then
    echo -e "${RED}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠶⣤⣄⣠⢤⣄⣤⢤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣼⣾⠛⠛⠲⣼⣷⡘⠿⢿⡏⣉⡓⠶⢤⣤⢤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⠿⠾⠟⠁⣤⣄⣀⣀⡀⠙⠓⠚⠷⡽⢿⣷⢀⣰⢿⣫⠿⠭⠟⠳⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⠦⣀⠈⣿⣶⡦⢤⣬⣉⣁⣛⣋⣀⣀⡀⠀⣶⣶⣌⠉⡿⠉⣽⣤⡀⠀⠸⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢦⡈⠻⣿⠛⠃⣸⢻⣿⡗⠀⢸⠀⠉⠁⠀⠈⠛⠋⠀⣧⢸⣿⣿⣿⡄⠀⢹⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⡴⠛⠛⠛⠛⠿⠿⣦⣉⣀⣠⡾⠆⠀⠀⠀⠀⠀⠀⠀⣿⠀⠻⣿⡿⠁⠀⣼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣴⠚⡹⠴⣶⠟⠛⠛⠛⢳⡶⠲⢤⣙⠣⣅⠓⢩⠀⠀⠀⠀⠀⠀⠀⠻⣄⣀⠀⠰⣶⣦⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢧⡈⠳⠤⠿⠤⠤⠤⠤⠚⠓⠒⠒⠚⠳⠬⠳⡀⢠⣤⣄⠀⠀⠀⠀⢠⠏⣏⠉⠙⠻⢿⣁⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠈⣙⣶⡖⠒⠂⠀⠀⠀⠀⠀⠀⠀⠀⠦⢤⠷⠈⠉⠁⠀⠀⠀⠀⠘⣦⠈⣧⡈⠙⠲⢌⡑⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀
⣀⣀⡀⠀⣀⠤⠒⣋⡥⠔⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠀⢿⣿⡆⠀⠀⡟⠒⢬⡓⢤⡀⠀⠀⠀⠀⠀
⠀⣀⣈⠉⣤⡖⠋⠀⠀⠀⠀⠳⣄⠀⠀⠀⠀⠀⠀⠀⢀⡼⠁⠀⠀⠀⠀⢀⣤⣤⡀⠀⢹⡄⠀⠈⢀⣀⠀⢷⠀⠀⠈⠳⢍⠲⣄⠀⠀⠀
⠉⠀⠈⠙⡇⢹⠀⠀⠀⠀⠀⠀⠈⣹⣶⠤⠤⢤⣤⣶⣯⣤⣄⣀⣀⣀⣀⠈⠻⡿⠋⠀⢰⠇⠀⢀⣈⣿⡧⣼⠀⠀⠀⠀⡠⠽⡞⠓⠢⢤
⠀⠀⠀⠀⠻⠾⠀⠀⠀⠀⠀⠀⠰⣏⣭⡀⢰⣿⣿⣿⣿⣿⣿⠀⠀⠀⠈⠉⠉⣩⣍⠉⢻⡏⢉⣅⡀⠀⠀⢸⡄⠀⠀⡞⣰⠊⠉⠳⡄⢰
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠔⣫⠵⠛⠙⠒⣾⣿⣿⣿⣿⣿⠦⢤⣀⣀⣀⣠⣿⡋⠀⣰⢃⣈⣛⣁⡤⠤⠼⠃⠀⠀⠉⠉⠀⠀⠀⠸⡌
⠀⠀⠀⣠⣤⠤⠖⠒⠊⠁⡖⠉⠀⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⠀⠀⠀⠈⠀⠀⠀⠉⠉⠉⠉⠙⢮⠻⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢧
⠀⠀⠀⢿⡿⠦⠔⠒⠒⠚⠁⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡱⠈⠓⠤⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⠦⠤⣄⣀⣨⣿⡷⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠀⠀⠀⠀⠀⠀⠀${COLOR}"
fi

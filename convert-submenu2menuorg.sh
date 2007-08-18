#!/bin/sh
#
# vdr-menuorg - A plugin for the Linux Video Disk Recorder
# Copyright (C) 2007 Thomas Creutz, Tobias Grimm
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# $Id$
#

usage="convert-submenu2menuorg.sh submenu-file menuorg-file"

if [ a"$1" ==  a"" ] || ! [ -f $1 ]; then echo $usage && exit 1; fi
if [ a"$2" ==  a"" ]; then echo $usage && exit 1; fi

declare -a menu

echo "read the input file"
while read line
do
    menuLevel=`echo $line|cut -d: -f1`
    kindOfItem=`echo $line|cut -d: -f2`
    name=`echo $line|cut -d: -f3`

    if [ $kindOfItem != 0 ]
    then
        menu[$menuLevel]="${menu[$menuLevel]} 0;$name"
    else
        menu[$menuLevel]="${menu[$menuLevel]} $name"
    fi

done < $1

echo "write the xml to the output file"
echo "<menus>" > $2
COUNT=0
for item in `echo ${menu[0]}`
do
    case $item
    in
        Schedule)   echo "    <system name=\"${item}\" />" >> $2;;
        Channels)   echo "    <system name=\"${item}\" />" >> $2;;
        Timers)     echo "    <system name=\"${item}\" />" >> $2;;
        Recordings) echo "    <system name=\"${item}\" />" >> $2;;
        Setup)      echo "    <system name=\"${item}\" />" >> $2;;
        Commands)   echo "    <system name=\"${item}\" />" >> $2;;

        0*)
            echo "    <menu name=\"$(echo $item|cut -d';' -f2)\">" >> $2

            COUNT=$(($COUNT+1))
            for Subitem in `echo ${menu[$COUNT]}`
            do
                case $item
                in
                    Schedule)   echo "        <system name=\"${Subitem}\" />" >> $2;;
                    Channels)   echo "        <system name=\"${Subitem}\" />" >> $2;;
                    Timers)     echo "        <system name=\"${Subitem}\" />" >> $2;;
                    Recordings) echo "        <system name=\"${Subitem}\" />" >> $2;;
                    Setup)      echo "        <system name=\"${Subitem}\" />" >> $2;;
                    Commands)   echo "        <system name=\"${Subitem}\" />" >> $2;;
                    *)          echo "        <plugin name=\"${Subitem}\" />" >> $2;;
                esac
            done

            echo "    </menu>" >> $2
            ;;

        *)          echo "    <plugin name=\"${item}\" />" >> $2;;
    esac
done
echo "</menus>" >> $2

echo done

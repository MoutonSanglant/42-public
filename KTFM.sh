#!/bin/bash

#-u: update definition files
#chown/chmod des fichiers
#-m moulinette
#-n norminette

                                        
echo "                                    \` .\`                            "
echo "                                   oMNMMmMmmo                       "
echo "                               /s-.NMMMMMMMMMo.-: \` -\`              "
echo "                               hMMmNMMMMMMMMMMMMMNMNMNNhdh+o-\`      "
echo "                                .mMMMMMMMMMMMMMMMMMMMMMMMMMMMm-     "
echo "                               :NMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM+    "
echo "                              .NMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMs   "
echo "                              :MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMo   "
echo "                               oMMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMs  "
echo "                                \`:.:\` dMMMMMMMMMMMMMMMMMMMMMMMN//.  "
echo "                                      .hMMMMMMMMMMMMMMMMMMMMMMm     "
echo "                                        /dmMMMMMMMMMMMMMMMMMMm\`     "
echo "                                          \`yMNdMMNhNMMMMMMhh:       "
echo "                                           sMh NMs :MM.+MM\`         "
echo "                                          /MMm NMy-NMM./MM.         "
echo "                                           .- :MMm /o/ oMM/         "
echo "                                             /NMMM-   sMMMy         "
echo "                                              .//-    -sys/         "
echo "                                                                    "
echo "                   KillTheFuckingMachine   v0.1                           "
echo "                      by Thierry Defresne (tdefresn@student.42.fr)             "
echo "                                                                    "
echo "                                                                    "
echo "                                                                    "


function get_definitions () {
while [ true  ]
do
	printf "Quel jour ? (07 pour jour-07, q pour quitter)\n"
	read day
	if [[ $day == [01][0-9] ]]
		then echo "Récupération des définitions..."
		rm ./.$day 2> /dev/null
		curl "https://raw.githubusercontent.com/MoutonSanglant/42/master/definitions/j$day" > ./.$day
		chmod 744 ./.$day
		chown $USER:$GROUP ./.$day
		if [[ $(cat ./.$day) == "Not Found" ]]
			then echo "j$day innaccessible"
		else
			cp ./.$day ./.tmp
			chmod 744 ./.tmp
			chown $USER:$GROUP ./.tmp
			make_project_directory $day
			break
		fi
	fi
done
}

function make_project_directory ()
{
if [ ! -d ./jour-$1 ]
	then mkdir "./jour-$1"
	chown $USER:$GROUP "./jour-$1"
fi
for ((j=1;j<100; j += 2));
do
	dir=$(cat ./.tmp | cut -d : -f $j)
	files=$(cat ./.tmp | cut -d : -f $(($j+1)))

	if [[ $files == "" ]]
	then
		break
	fi

	make_project_c_and_h $1 $dir $files
done
}

function make_project_c_and_h
{
proj="./jour-$1/$2"
if [ ! -d $proj ]
then	
	mkdir $proj
	chown $USER:$GROUP $proj
fi

for ((i=1; i<10; i++));
do
	file=$(echo $3 | cut -d , -f $i)
	if [[ $file == "" ]]
	then
		break
	fi
	touch $proj/$file
	chmod 744 $proj/$file
	chown $USER:$GROUP $proj/$file
done
}


[ -s ./.config/f1 ]
if [[ $? ]]
	then
		printf "Ajouter un projet dans %s ?\n" "${PWD##*/}"
	else
		printf "Créer un projet dans %s ?\n" "${PWD##*/}"
	fi
read  yn
if [[ $yn =~ ^[OoYy] ]]
	then get_definitions
else
	echo "Bye"
fi

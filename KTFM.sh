#!/bin/bash

# Options:
# -u: force definition files update
# -m moulinette
# -n norminette
# -g ... git ...

year=2015

while [[ $# > 1 ]]
do
key="$1"

case $key in
	-n|--norminette)
	NORMINETTE="$2"
	shift # past argument
	;;
	-m|--moulinette)
	MOULINETTE="$2"
	shift # past argument
	;;
	-g|--git)
	GIT=Y
	shift # past argument
	;;
	*)
	
	;;
esac
shift # past argument or value
done


echo "                                                                    "
echo "                                                                    "
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
echo "                   KillTheFuckingMachine   vb.13                          "
echo "                      by Thierry Defresne (tdefresn@student.42.fr)             "
echo "                                                                    "
echo "                                                                    "
echo "                                                                    "
echo "  ***Disclaimer***: aucun mouton ne peut être considéré responsable de vos mauvaises manipulations lors de l'utilisation de ce script (mais on essaie de vous empêcher au mieux de faire des bétises avec).         "
echo "                                                                    "
echo "  ***Warning***: si vous n'avez pas téléchargé ce script directement sur 'https://github.com/MoutonSanglant/42', vous êtes probablement victime d'un vilain troll.                                                                  "
echo "                                                                    "
echo "                                                                    "
echo "                                                                    "

function get_definitions () {
while [ true  ]
do
	bypass=0
	printf "Quel jour ? (07 pour le jour 07, # pour un projet spécial (ex. "ColleXX"), q pour quitter)\n"
	read day
	if [[ $day == "#" ]]
	then
		day=""
		while [ true ]
		do
		printf "Projet ?\n1: Match-N-Match\n0: annuler\n"
		read  project
		case $project in
			1)
			day="Match-N-Match"
			bypass=1
			break
			;;
			0)
			break
			;;
			*)
			
			;;
		esac
		done
	fi
	if [[ $day == [01][0-9] || bypass -ne 0 ]]
	then
		echo "Nom du dossier (laisser vide pour 'jour-$day'): "
		read  prefix
		if [[ $prefix == "" ]]
			then
			prefix="jour-"
		fi
		if [[ -d "./$prefix$day" ]]
		then
			while [ true ]
			do
			echo "Un dossier './$prefix$day' existe déjà, supprimer ? (x pour quitter)"
			read  yn
			if [[ $yn =~ ^[OoYy] ]]
				then break
			elif [[ $yn =~ ^[nNXx] ]]
				then exit
			fi
			done
		fi
		if [[ $dirname$day == "" ]]
		then
			echo "Bad folder access, exiting"
			exit
		fi
		rm -rf "./$prefix$day"
		echo "Récupération des définitions..."
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
			make_project_directory $day $prefix
			if [[ $NORMINETTE == "y" ]]
			then
				echo "Passage de la norminette"
				norminette --CheckForbiddenSourceHeader "./$prefix$day/*/*.c"
			fi
			break
		fi
	elif [[ $day == [Qq] ]]
		then exit
	fi
done
}

function git_clone_project_directory ()
{
	gitcmd=vgs:intra/$year/activities/jour_$1/$USER
	echo "Cloning from git: $gitcmd"
	git clone $gitcmd $2
	giterror=$?
	if [[ $giterror != 0 ]]
	then
		echo "Impossible de cloner le git, la commande est mal écrite ? (erreur git: $giterror)"
		exit
	fi
}

function make_project_directory ()
{
if [ ! -d ./$2$1 ]
	then mkdir "./$2$1"
	chown $USER:$GROUP "./$2$1"
fi

git_clone_project_directory $1 $2$1

for ((j=1;j<100; j += 2));
do
	dir=$(cat ./.tmp | cut -d : -f $j)
	files=$(cat ./.tmp | cut -d : -f $(($j+1)))

	if [[ $files == "" ]]
	then
		break
	fi

	make_project_c_and_h $1 $dir $files $2
done
}

function make_project_c_and_h
{
exercice="./$4$1/$2"
if [ ! -d $exercice ]
then
	mkdir $exercice
	chown $USER:$GROUP $exercice
fi

for ((i=1; i<10; i++));
do
	file=$(echo $3 | cut -d , -f $i)
	if [[ $file == "" || -d $exercice/$file ]]
	then
		echo "File $file already exist."
		break
	fi
	touch $exercice/$file
	chmod 744 $exercice/$file
	chown $USER:$GROUP $exercice/$file
done
}


[ -s ./.config/f1 ]
if [[ $? ]]
	then
		printf "Ajouter un projet dans '%s' ?\n" "${PWD##*/}"
	else
		printf "Créer un projet dans '%s' ?\n" "${PWD##*/}"
	fi
read  yn
if [[ $yn =~ ^[OoYy] ]]
	then get_definitions
else
	echo "Bye"
fi

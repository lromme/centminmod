#######################################################################################
# MariaDB MySQL Upgrade sub menu
#######################################################################################
ENABLE_MARIADBTENUPGRADE='y'

mariadbsubmenu() {

while :
do
	# clear
        # display menu
	echo
	cecho "--------------------------------------------------------" $boldyellow
	cecho "        MariaDB MySQL Upgrade Sub-Menu              " $boldgreen
	cecho "--------------------------------------------------------" $boldyellow
	cecho "1). MariaDB 5.2.x Branch Upgrade Only" $boldgreen
	cecho "2). MariaDB 5.2.x to MariaDB 5.5 YUM upgrade" $boldgreen
	cecho "3). MariaDB 5.5 to MariaDB 10.x YUM upgrade" $boldgreen
	cecho "4). MariaDB 5.5 to MariaDB 10.1.x YUM upgrade" $boldgreen
	cecho "5). MariaDB 10.x to MariaDB 10.1.x YUM upgrade" $boldgreen
	cecho "6). Back to Main menu" $boldgreen
	cecho "--------------------------------------------------------" $boldyellow

	read -ep "Enter option [ 1 - 6 ] " mmoption
	cecho "--------------------------------------------------------" $boldyellow

#########################################################

case "$mmoption" in
1)

centminlog
{
MARIADBVERCHECK=`rpm -qa | grep MariaDB-server | awk -F "-" '{print $3}' | cut -c1-3`

# for MariaDB 5.2 upgrade option
if [[ "$MARIADBVERCHECK" == '5.3' || "$MARIADBVERCHECK" == '5.5' ]]; then

echo ""
cecho "MariaDB 5.3.x or 5.5.x server detected" $boldyellow
cecho "downgrading to MariaDB 5.2.x is not recommended" $boldyellow
cecho "aborting MariaDB 5.2.x upgrade option..." $boldyellow
sleep 5
exit

else

funct_mariadbupgrade

fi
} 2>&1 | tee ${CENTMINLOGDIR}/centminmod_${SCRIPT_VERSION}_${DT}_mariadb52_upgrade.log

;;
2)

centminlog
{
MARIADBVERCHECK=`rpm -qa | grep MariaDB-server | awk -F "-" '{print $3}' | cut -c1-3`

# for MariaDB 5.5 upgrade option
if [ "$MARIADBVERCHECK" == '5.5' ]; then

echo ""
cecho "MariaDB 5.5.x server already detected" $boldyellow
cecho "MariaDB 5.5 uses normal YUM commands for updates as follows:" $boldyellow
echo ""
cecho " yum update --disablerepo=CentALT MariaDB-client MariaDB-common MariaDB-compat MariaDB-devel MariaDB-server MariaDB-shared MariaDB-test" $boldgreen
echo ""
cecho "aborting MariaDB 5.5.x upgrade option..." $boldyellow
sleep 5
exit

else

mariadbfiveupgrade

fi
} 2>&1 | tee ${CENTMINLOGDIR}/centminmod_${SCRIPT_VERSION}_${DT}_mariadb55_upgrade.log

;;
3)

centminlog
{
MARIADBVERCHECK=`rpm -qa | grep MariaDB-server | awk -F "-" '{print $3}' | cut -c1-4`
	if [ "$MARIADBVERCHECK" == '10.0' ]; then

		echo ""
		cecho "MariaDB 10.x server already detected" $boldyellow

	else

		if [[ "$ENABLE_MARIADBTENUPGRADE" = [nN] ]]; then
			echo "Place holder for now until MariaDB 10.x is ready to be added"
		else
			mariadbtenpgrade
		fi
	fi
} 2>&1 | tee ${CENTMINLOGDIR}/centminmod_${SCRIPT_VERSION}_${DT}_mariadb10_upgrade.log
;;
4)

centminlog
{
MARIADBVERCHECK=`rpm -qa | grep MariaDB-server | awk -F "-" '{print $3}' | cut -c1-4`
	if [ "$MARIADBVERCHECK" == '10.1' ]; then

		echo ""
		cecho "MariaDB 10.1.x server already detected" $boldyellow

	else

		if [[ "$ENABLE_MARIADBTENUPGRADE" = [nN] ]]; then
			echo "Place holder for now until MariaDB 10.1.x is ready to be added"
		else
			echo "Place holder for now until MariaDB 10.1.x is ready to be added"
			# mariadbfivetotenoneupgrade
		fi
	fi
} 2>&1 | tee ${CENTMINLOGDIR}/centminmod_${SCRIPT_VERSION}_${DT}_mariadb_55-to-10-1_upgrade.log
;;
5)

centminlog
{
MARIADBVERCHECK=`rpm -qa | grep MariaDB-server | awk -F "-" '{print $3}' | cut -c1-4`
	if [ "$MARIADBVERCHECK" == '10.1' ]; then

		echo ""
		cecho "MariaDB 10.1.x server already detected" $boldyellow

	else

		if [[ "$ENABLE_MARIADBTENUPGRADE" = [nN] ]]; then
			echo "Place holder for now until MariaDB 10.1.x is ready to be added"
		else
			echo "Place holder for now until MariaDB 10.1.x is ready to be added"
			# mariadbtentotenoneupgrade
		fi
	fi
} 2>&1 | tee ${CENTMINLOGDIR}/centminmod_${SCRIPT_VERSION}_${DT}_mariadb_10-to-10-1_upgrade.log
;;
6)
	break
;;
esac
done

}


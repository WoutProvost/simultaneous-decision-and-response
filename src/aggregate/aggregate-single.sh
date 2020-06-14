#!/bin/bash
shopt -s extglob

echo "==========INDIVIDUAL=========="
echo "----------SYMMETRIC----------"
ls individual_0.0_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-symmetric individual_0.0_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC----------"
ls individual_!(0.0)_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric individual_!(0.0)_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-2.5----------"
ls individual_2.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric individual_2.5_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-2.0----------"
ls individual_2.0_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric individual_2.0_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-1.5----------"
ls individual_1.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric individual_1.5_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-1.0----------"
ls individual_1.0_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric individual_1.0_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-0.5----------"
ls individual_0.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric individual_0.5_*.csv
else
	echo "No data"
fi
echo ""

echo "==========MAJORITY=========="
echo "----------SYMMETRIC----------"
ls majority_0.0_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-symmetric majority_0.0_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC----------"
ls majority_!(0.0)_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric majority_!(0.0)_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-2.5----------"
ls majority_2.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric majority_2.5_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-2.0----------"
ls majority_2.0_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric majority_2.0_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-1.5----------"
ls majority_1.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric majority_1.5_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-1.0----------"
ls majority_1.0_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric majority_1.0_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-0.5----------"
ls majority_0.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric majority_0.5_*.csv
else
	echo "No data"
fi
echo ""

echo "==========QUALITY=========="
echo "----------SYMMETRIC----------"
ls quality_0.0_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-symmetric quality_0.0_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC----------"
ls quality_!(0.0)_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric quality_!(0.0)_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-2.5----------"
ls quality_2.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric quality_2.5_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-2.0----------"
ls quality_2.0_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric quality_2.0_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-1.5----------"
ls quality_1.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric quality_1.5_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-1.0----------"
ls quality_1.0_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric quality_1.0_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-0.5----------"
ls quality_0.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric quality_0.5_*.csv
else
	echo "No data"
fi
echo ""

echo "==========RANDOM=========="
echo "----------SYMMETRIC----------"
ls random_0.0_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-symmetric random_0.0_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC----------"
ls random_!(0.0)_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric random_!(0.0)_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-2.5----------"
ls random_2.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric random_2.5_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-2.0----------"
ls random_2.0_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric random_2.0_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-1.5----------"
ls random_1.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric random_1.5_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-1.0----------"
ls random_1.0_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric random_1.0_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC y=-0.5----------"
ls random_0.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate-non-symmetric random_0.5_*.csv
else
	echo "No data"
fi
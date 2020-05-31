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
	~/Desktop/aggregate-symmetric individual_!(0.0)_*.csv
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
	~/Desktop/aggregate-symmetric majority_!(0.0)_*.csv
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
	~/Desktop/aggregate-symmetric quality_!(0.0)_*.csv
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
	~/Desktop/aggregate-symmetric random_!(0.0)_*.csv
else
	echo "No data"
fi
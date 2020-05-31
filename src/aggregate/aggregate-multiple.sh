#!/bin/bash
shopt -s extglob

echo "==========INDIVIDUAL=========="
echo "----------SYMMETRIC----------"
ls individual_0.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate individual_0.5_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC----------"
ls individual_!(0.5)_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate individual_!(0.5)_*.csv
else
	echo "No data"
fi
echo ""

echo "==========MAJORITY=========="
echo "----------SYMMETRIC----------"
ls majority_0.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate majority_0.5_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC----------"
ls majority_!(0.5)_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate majority_!(0.5)_*.csv
else
	echo "No data"
fi
echo ""

echo "==========QUALITY=========="
echo "----------SYMMETRIC----------"
ls quality_0.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate quality_0.5_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC----------"
ls quality_!(0.5)_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate quality_!(0.5)_*.csv
else
	echo "No data"
fi
echo ""

echo "==========RANDOM=========="
echo "----------SYMMETRIC----------"
ls random_0.5_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate random_0.5_*.csv
else
	echo "No data"
fi
echo "----------NON-SYMMETRIC----------"
ls random_!(0.5)_*.csv > /dev/null 2>&1
if [ $? -eq 0 ]; then
	~/Desktop/aggregate random_!(0.5)_*.csv
else
	echo "No data"
fi
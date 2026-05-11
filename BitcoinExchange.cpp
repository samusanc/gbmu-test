/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:13:48 by samusanc          #+#    #+#             */
/*   Updated: 2024/07/21 13:51:56 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cstring>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <limits.h>

long double	stringToLongDouble(std::string str)
{
	char		*e;
	const char	*val = str.c_str();
	errno = 0;
	long double result = std::strtold(val, &e);

	if (*e != '\0' || errno != 0)
	{
		throw std::out_of_range ("Value: ");
	}
	return (result);
}

long double	checkFloat(const std::string str)
{
	int	i = 0;
	int	f = 0;
	int	point = 0;
	int	sign = 0;

	while (i != (int)(str.length()))
	{
		if (!isdigit(str[i]))
		{
			if ((str[i] == '-' || str[i] == '+') && i == 0)
			{
				throw std::out_of_range ("not a positive number.");
			}
			if (str[i] == '.' && (i != (int)(str.length() - 1) || i != 0))
				point++;
			else if (str[i] == '.')
			{
				throw std::out_of_range ("Value: bad point.");
			}
			if (str[i] == 'f' && i == (int)(str.length() - 1) && i != 0)
				f++;
			else if (str[i] == 'f')
			{
				throw std::out_of_range ("Value: bad float 'f'.");
			}
		}
		i++;
	}
	if (f > 1 || point > 1 || sign > 1)
	{
		throw std::out_of_range ("Value: double point, sign or f.");
	}
	if (f != 0)
		return (stringToLongDouble(static_cast<std::string>(str).erase(static_cast<std::string>(str).find("f", 0))));
	return (stringToLongDouble(str));
}

void	checkNAD(char *str)//check numbers and dash
{
	int	i;
	int	dash;

	i = 0;
	dash = 0;
	if (str[0] == '-')
		throw std::out_of_range ("Date: NULL.");
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (str[i] == '-')
				dash++;
			else
				throw std::out_of_range ("Date: NULL.");
		}
		i++;
	}
	if (dash != 2)
	{
		throw std::out_of_range ("Date: NULL.");
	}
}

int	limitDateChecker(char *str)
{
	long double	checker;
	std::string tmp(str);
	
	checker = checkFloat(tmp);
	if (checker > INT_MAX)
		throw std::out_of_range ("Date:");
	return (static_cast<int>(checker));
}

void	checkDays(int month, int day)
{
	switch (month)
	{
		case 1:
			if (day > 31)
				throw std::out_of_range ("Date: day.");
			break ;
		case 2:
			if (day > 29)
				throw std::out_of_range ("Date: day.");
			break ;
		case 3:
			if (day > 31)
				throw std::out_of_range ("Date: day.");
			break ;
		case 4:
			if (day > 30)
				throw std::out_of_range ("Date: day.");
			break ;
		case 5:
			if (day > 31)
				throw std::out_of_range ("Date: day.");
			break ;
		case 6:
			if (day > 30)
				throw std::out_of_range ("Date: day.");
			break ;
		case 7:
			if (day > 31)
				throw std::out_of_range ("Date: day.");
			break ;
		case 8:
			if (day > 31)
				throw std::out_of_range ("Date: day.");
			break ;
		case 9:
			if (day > 30)
				throw std::out_of_range ("Date: day.");
			break ;
		case 10:
			if (day > 31)
				throw std::out_of_range ("Date: day.");
			break ;
		case 11:
			if (day > 30)
				throw std::out_of_range ("Date: day.");
			break ;
		case 12:
			if (day > 31)
				throw std::out_of_range ("Date: day.");
			break ;
	}
}

int	*checkEachDate(char *str)
{
	int		year;
	int		month;
	int		day;
	int		i;
	
	i = 0;
	year = 0;
	month = 0;
	day = 0;
	str = strtok(str, "-");
	while (str)
	{
		if (!i)
		{
			year = limitDateChecker(str);
		}
		else if (i == 1)
		{
			month = limitDateChecker(str);
			if (month > 12 || month == 0)
				throw std::out_of_range ("Date: month.");
		}
		else if (i == 2)
		{
			day = limitDateChecker(str);
			checkDays(month, day);
		}
		str = strtok(NULL, "-");
		i++;
	}
	if (i != 3)
		throw std::out_of_range ("Date: null");
	int		*date;

	date = new int[3];
	date[0] = year;
	date[1] = month;
	date[2] = day;
	return (date);
}

int	*checkDate(char *date)
{
	int	*result;

	result = NULL;
	checkNAD(date);
	result = checkEachDate(date);
	return (result);
}

void	BitcoinExchange::parse_db(char *str)
{
	std::string	date;
	std::string	value;
	int		*d;
	int		i;
	float		v;

	i = 0;
	str = strtok(str, ",");
	if (!str)//end of file
		return ;
	while (str)
	{
		if (!i)
		{
			if (str)
				date = std::string(str);
			else
				throw std::out_of_range ("Data base: null");
		}
		else
		{
			if (str)
				value = std::string(str);
			else
				throw std::out_of_range ("Data base: null");
		}
		str = strtok(NULL, ",");
		i++;
	}
	if (i != 2)
		throw std::out_of_range ("Data base: hola");
	d = checkDate(const_cast<char *>(date.c_str()));
	try
	{
		v = static_cast<float>(checkFloat(value));
	}
	catch (const std::exception& e)
	{
		delete [] d;
		throw std::out_of_range (e.what());
	}
	db.insert(std::pair<int *, float>(d, v));
}

float	BitcoinExchange::getAproxValue(int *date)
{
	std::map<int *, float>::iterator	i = db.begin();
	std::map<int *, float>::iterator	e = db.end();

	while (i != e)
	{
		if (i->first[0] > date[0])
		{
			--i;
			return (i->second);
		}
		else if (i->first[0] == date[0])
		{
			if (i->first[1] > date[1])
			{
				--i;
				return (i->second);
			}
			else if (i->first[1] == date[1])
			{
				if (i->first[2] > date[2])
				{
					--i;
					return (i->second);
				}
			}
		}
		i++;
	}
	--i;
	return (i->second);
}

void	BitcoinExchange::parse_infile(char *str)
{
	if (str)
	{
		std::string	in(str);
		std::string	date;
		std::string	value;
		int		*d;
		int		i;
		float		v;
	
		i = 0;
		str = strtok(str, " | ");
		if (!str)//end of file
			return ;
		while (str)
		{
			if (!i)
			{
				if (str)
					date = std::string(str);
				else
					throw std::out_of_range ("bad input: null");
			}
			else
			{
				if (str)
					value = std::string(str);
				else
					throw std::out_of_range ("bad input: null");
			}
			str = strtok(NULL, " | ");
			i++;
		}
		if (i != 2)
			throw std::out_of_range ("bad input => " + in);
		d = checkDate(const_cast<char *>(date.c_str()));
		try
		{
			v = static_cast<float>(checkFloat(value));
		}
		catch (const std::exception& e)
		{
			delete [] d;
			throw std::out_of_range (e.what());
		}
		if (v > 1000)
		{
			delete [] d;
			throw std::out_of_range ("too large number.");
		}
		std::cout << d[0] << "-";
 		if (d[1] < 10)
			std::cout << "0" << d[1];
		else
			std::cout << d[1];
 		if (d[2] < 10)
 			std::cout << "-" << "0" << d[2] << " => ";
		else
 			std::cout << "-" << d[2] << " => ";
		std::cout << v << " = " << getAproxValue(d) * v << std::endl;
		delete [] d;
	}
}

BitcoinExchange::BitcoinExchange(std::ifstream& dataBase, std::ifstream& in)
{
	std::string	dataB;
	std::string	iN;

	std::getline(dataBase, dataB);
	if (dataB != "date,exchange_rate")//exception in case bad header of data base
	{
		this->clear();
		throw std::out_of_range ("Data base: bad header.");
	}
	// Every exception produced in the data base is handle like an program error.
	while (dataBase)
	{
		std::getline(dataBase, dataB);
		try
		{
			parse_db(const_cast<char *>(dataB.c_str()));
		}
		catch (const std::exception& e)
		{
			this->clear();
			throw std::out_of_range("Data base: " + std::string(e.what()));
		}
	}
	std::getline(in, iN);
	if (iN != "date | value")//exception in case bad header of in file
	{
		this->clear();
		throw std::out_of_range ("Input file: bad header.");
	}
	// Every exception produced in the input is handle individually and not as an program error
	while (in)
	{
		std::getline(in, iN);
		try
		{
			parse_infile(const_cast<char *>(iN.c_str()));
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
}

void	BitcoinExchange::clear()
{
	std::map<int *, float>::iterator	i = db.begin();
	std::map<int *, float>::iterator	e = db.end();

	while (i != e)
	{
		delete [] i->first;
		i++;
	}
	db.clear();
}

BitcoinExchange::~BitcoinExchange()
{
	this->clear();
}

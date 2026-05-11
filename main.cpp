/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 08:36:52 by samusanc          #+#    #+#             */
/*   Updated: 2024/07/20 16:10:53 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: could not open file." << std::endl;
		return (-1);
	}

	std::ifstream	infile(*++argv);
	std::ifstream	dataBase("data.csv");

	if (!dataBase.is_open())
	{
		std::cout << "Error: read data base file: " << "data.csv" << " is impossible" << std::endl;
		return (-1);
	}
	if (!infile.is_open())
	{
		std::cout << "Error: read input file: " << *argv << " is impossible" << std::endl;
		dataBase.close();
		return (-1);
	}

	try
	{
		BitcoinExchange machine(dataBase, infile);
		infile.close();
		dataBase.close();
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;  
		infile.close();
		dataBase.close();
		return (-1);
	}
	return (0);
}

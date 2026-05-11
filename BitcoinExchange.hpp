/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:56:16 by samusanc          #+#    #+#             */
/*   Updated: 2024/07/21 13:50:26 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef	BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <string>
# include <iostream>
# include <fstream>
# include <map>

class	BitcoinExchange{
	/* here every public statement */
	public:
		/* Destructor */
		~BitcoinExchange(void);
		BitcoinExchange(std::ifstream& dataBase, std::ifstream& in);

	/* here every private statement */
	private:
		/* Constructor */
		BitcoinExchange(void);
		/* Copy Constructor */
		BitcoinExchange(const BitcoinExchange& other);
		/* Copy assignment operator overload */
		BitcoinExchange& operator = (const BitcoinExchange& other);

		void parse_db(char *str);
		void parse_infile(char *str);
		void clear();
		float	getAproxValue(int *date);

		std::map<int *, float>	db;
		std::map<int *, float>	input;
};

#endif

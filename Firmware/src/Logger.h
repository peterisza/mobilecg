/*
 * Logger.h
 *
 *  Created on: 2015. dec. 22.
 *      Author: xdever
 */

#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

class Logger {
public:
	Logger();
	virtual ~Logger();

	static void panic(const char *message);
};

#endif /* SRC_LOGGER_H_ */

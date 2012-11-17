/**
 * @file /include/ecl/devices/serial_parameters.hpp
 *
 * @brief Cross-platform abstractions for the serial class.
 *
 * @date September 2009
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_DEVICES_SERIAL_PARAMETERS_HPP_
#define ECL_DEVICES_SERIAL_PARAMETERS_HPP_

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Enums
*****************************************************************************/

/**
 * @brief Serial connection baud rate.
 *
 * The baud rate of a serial connection.
 **/
enum BaudRate {
    BaudRate_110,
    BaudRate_300,
    BaudRate_600,
    BaudRate_1200,
    BaudRate_2400,
    BaudRate_4800,
    BaudRate_9600,
    BaudRate_19200,
    BaudRate_38400,
    BaudRate_57600,
    BaudRate_115200,
    BaudRate_921600
};

/**
 * @brief Data bits used in a serial packet.
 *
 * The number of data bits used in the serial protocol.
 **/
enum DataBits {
    DataBits_5 = 0,
    DataBits_6,
    DataBits_7,
    DataBits_8,
};

/**
 * @brief Stop bits used in a serial packet.
 *
 * Number of stop bits used in the serial protocol.
 **/
enum StopBits {
    StopBits_1 = 0,
    StopBits_15,
    StopBits_2
};

/**
 * @brief Parity of the serial packet.
 *
 * Parity of the serial communication.
 **/
enum Parity {
    NoParity = 0,
    OddParity = 1,
    EvenParity = 2
};

} // namespace ecl

#endif /* ECL_DEVICES_SERIAL_PARAMETERS_HPP_ */

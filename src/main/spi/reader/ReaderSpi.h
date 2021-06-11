/**************************************************************************************************
 * Copyright (c) 2021 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * See the NOTICE file(s) distributed with this work for additional information regarding         *
 * copyright ownership.                                                                           *
 *                                                                                                *
 * This program and the accompanying materials are made available under the terms of the Eclipse  *
 * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                  *
 *                                                                                                *
 * SPDX-License-Identifier: EPL-2.0                                                               *
 **************************************************************************************************/

#pragma once

#include <cstdint>
#include <list>
#include <memory>
#include <string>
#include <vector>

namespace keyple {
namespace core {
namespace plugin {
namespace spi {
namespace reader {

/**
 * Reader able to communicate with smart cards whose purpose is to remain present in the reader (for
 * example a SAM reader).
 *
 * @since 2.0
 */
class ReaderSpi {
public:
    /**
     * Gets the name of the reader.
     *
     * @return A not empty string.
     * @since 2.0
     */
    virtual const std::string& getName() = 0;

    /**
     * Indicates if the provided reader protocol is supported by the reader.
     *
     * <p>Using this method allows to invoke the {@link #activateProtocol(String)} method only if
     * the protocol is supported.
     *
     * @param readerProtocol The reader protocol.
     * @return True if the protocol is supported, false if not.
     * @since 2.0
     */
    virtual bool isProtocolSupported(const std::string& readerProtocol) const = 0;

    /**
     * Activates a specific protocol in order to make the reader able to communicate with the cards
     * using this protocol.
     *
     * @param readerProtocol The reader specific protocol to activate.
     * @since 2.0
     */
    virtual void activateProtocol(const std::string& readerProtocol) = 0;

    /**
     * Deactivates a specific protocol so that the reader ignores cards using this protocol.
     *
     * @param readerProtocol The reader specific protocol to deactivate.
     * @since 2.0
     */
    virtual void deactivateProtocol(const std::string& readerProtocol) = 0;

    /**
     * Tells if the current card communicates with the provided protocol.
     *
     * @param readerProtocol The reader protocol to check.
     * @return true if the current protocol corresponds to the one provided, false if not.
     * @since 2.0
     */
    virtual bool isCurrentProtocol(const std::string& readerProtocol) const = 0;

    /**
     * Attempts to open the physical channel (to established a communication with the card).
     *
     * @throw ReaderIOException If the communication with the reader has failed.
     * @throw CardIOException If the communication with the card has failed.
     * @since 2.0
     */
    virtual void openPhysicalChannel() = 0;

    /**
     * Attempts to close the current physical channel.
     *
     * <p>The physical channel may have been implicitly closed previously by a card withdrawal.
     *
     * @throw ReaderIOException If the communication with the reader has failed.
     * @since 2.0
     */
    virtual void closePhysicalChannel() = 0;

    /**
     * Tells if the physical channel is open or not.
     *
     * @return True is the physical channel is open, false if not.
     */
    virtual bool isPhysicalChannelOpen() const = 0;

    /**
     * Verifies the presence of a card.
     *
     * @return True if a card is present
     * @throw ReaderIOException If the communication with the reader has failed.
     * @since 2.0
     */
    virtual bool checkCardPresence() = 0;

    /**
     * Gets the power-on data.
     *
     * <p>The power-on data is defined as the data retrieved by the reader when the card is
     * inserted.
     *
     * <p>In the case of a contact reader, this is the Answer To Reset data (ATR) defined by
     * ISO7816.
     *
     * <p>In the case of a contactless reader, the reader decides what this data is. Contactless
     * readers provide a virtual ATR (partially standardized by the PC/SC standard), but other
     * devices can have their own definition, including for example elements from the anti-collision
     * stage of the ISO14443 protocol (ATQA, ATQB, ATS, SAK, etc).
     *
     * @return A not empty array
     * @since 2.0
     */
    virtual const std::vector<uint8_t>& getPowerOnData() const = 0;

    /**
     * Transmits an APDU and returns its response.
     *
     * <p><b>Caution: the implementation must handle the case where the card response is 61xy and
     * execute the appropriate get response command.</b>
     *
     * @param apduIn The data to be sent to the card.
     * @return A buffer of at least 2 bytes.
     * @throw ReaderIOException If the communication with the reader has failed.
     * @throw CardIOException If the communication with the card has failed.
     * @since 2.0
     */
    virtual const std::vector<uint8_t> transmitApdu(const std::vector<uint8_t>& apduIn) = 0;

    /**
     * Tells if the reader is a contactless type.
     *
     * C++ note: this function cannot be set 'const' as some derived classes will set internal
     *           flags accordingly.
     *
     * @return True if the reader a contactless type, false if not
     * @since 2.0
     */
    virtual bool isContactless() = 0;

    /**
     * Invoked when unregistering the associated plugin.
     *
     * @since 2.0
     */
    virtual void unregister() = 0;
};

}
}
}
}
}

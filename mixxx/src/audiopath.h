/**
 * @file audiopath.h
 * @author Bill Good <bkgood at gmail dot com>
 * @date 20100611
 */

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <QString>

/**
 * @class ChannelGroup
 * @brief Describes a group of channels, typically a pair for stereo sound in Mixxx.
 */
class ChannelGroup {
public:
    ChannelGroup(unsigned int channelBase, unsigned int channels);
    inline bool operator==(const ChannelGroup &other) const;
    inline bool clashesWith(const ChannelGroup &other) const;
private:
    unsigned int m_channelBase; // base (first) channel used on device 
    unsigned int m_channels; // number of channels used (s/b 2 in most cases)
};

/**
 * @class AudioPath
 * @brief Describes a path for audio to take.
 * @warning Shouldn't be instantiated, use one of the subclasses.
 */
class AudioPath {
public:
    AudioPath(unsigned int channelBase, unsigned int channels);
    bool channelsClash(const AudioPath& other) const;
    ChannelGroup getChannelGroup() const;
protected:
    ChannelGroup m_channelGroup;
private:
};

/**
 * @class AudioSource
 * @extends AudioPath
 * @brief A source of audio in Mixxx that is to be output to a group of
 *        channels on an audio interface.
 */
class AudioSource : public AudioPath {
public:
    enum AudioSourceType { 
        MASTER,
        HEADPHONES,
        DECK,
        PASSTHROUGH,
        MICROPHONE
    };
    AudioSource(AudioSourceType type, unsigned int channelBase,
                unsigned int channels, unsigned int index = 0);
    bool operator==(const AudioSource& other) const;
	QString getString() const;
private:
    AudioSourceType m_type;
    unsigned int m_index; // index of indexed sources (ex. decks)
};

/**
 * @class AudioReceiver
 * @extends AudioPath
 * @brief A source of audio at a group of channels on an audio interface
 *        that is be processed in Mixxx.
 */
class AudioReceiver : public AudioPath {
public:
    enum AudioReceiverType { 
		VINYLCONTROL,
		MICROPHONE,
    	PASSTHROUGH
    };
    AudioReceiver(AudioReceiverType type, unsigned int channelBase,
                unsigned int channels, unsigned int index = 0);
    bool operator==(const AudioReceiver& other) const;
	QString getString() const;
private:
    AudioReceiverType m_type;
    unsigned int m_index; // index of indexed sources (ex. decks)
};

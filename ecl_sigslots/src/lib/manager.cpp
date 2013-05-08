/**
 * @file /src/lib/manager.cpp
 *
 * @brief Implementation for SigSlotManager.
 *
 * Implementation for SigSlotManager.
 *
 * @date May 2013
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../../include/ecl/sigslots/manager.hpp"
#include "../../include/ecl/sigslots/sigslot.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {


/*****************************************************************************
** Implementation for Void type specialization
*****************************************************************************/

void SigSlotsManager<Void>::printStatistics()
{
	std::cout << "Topics" << std::endl;
	std::map< std::string, Topic<Void> >::iterator iter;
	for ( iter = topics().begin(); iter != topics().end(); ++iter ) {
		std::cout << iter->second;
	}
}

const Topic<Void>::Subscribers* SigSlotsManager<Void>::connectSignal(const std::string& topic, SigSlot<Void>* sigslot)
{
	// Try and insert a new topic in case it doesn't already exist
	// In any case, we always get the iterator back (to new or existing)
	//
	// Maybe improve the efficiency of this by specifying position
	// refer to http://www.cplusplus.com/reference/stl/map/insert/
	std::pair< std::map< std::string, Topic<Void> >::iterator,bool> ret = topics().insert( std::pair< std::string, Topic<Void> >(topic, Topic<Void>(topic)) );
	Topic<Void>& current_topic = (ret.first)->second;
	current_topic.addPublisher(sigslot);
	return current_topic.subscribers();
}

void SigSlotsManager<Void>::connectSlot(const std::string& topic, SigSlot<Void>* sigslot)
{
	// Try and insert a new topic in case it doesn't already exist
	// In any case, we always get the iterator back (to new or existing)
	//
	// Maybe improve the efficiency of this by specifying position
	// refer to http://www.cplusplus.com/reference/stl/map/insert/
	std::pair< std::map< std::string, Topic<Void> >::iterator,bool> ret = topics().insert(std::pair< std::string, Topic<Void> >(topic, Topic<Void>(topic)) );
	Topic<Void>& current_topic = (ret.first)->second;
	current_topic.addSubscriber(sigslot);
}

void SigSlotsManager<Void>::disconnect(const std::string& topic, SigSlot<Void>* sigslot)
{
	std::map<std::string, Topic<Void> >::iterator iter = topics().find(topic);
	if ( iter != topics().end() ) {
		iter->second.disconnect(sigslot);
	}
	if ( iter->second.empty() ) {
		topics().erase(iter);
	}
}

bool SigSlotsManager<Void>::isTopic(const std::string& topic)
{
	return !( topics().find(topic) == topics().end() );
}

std::map< std::string, Topic<Void> >& SigSlotsManager<Void>::topics()
{
	static std::map< std::string, Topic<Void> > topic_list;
	return topic_list;
}

const SigSlotsManager<Void>::Subscribers& SigSlotsManager<Void>::subscribers(const std::string& topic)
{
	std::map< std::string, Topic<Void> >::const_iterator iter = topics().find(topic);
	/*
	 * Note that this is called only by SigSlotsManager::connectSignal which
	 * makes sure the topic name exists, so we don't need to do any error
	 * handling here.
	 */
	// ecl_assert_throw( iter != topics().end(), StandardException(LOC,InvalidInputError,std::string("No sigslots topic with name:")+topic) );
	return *iter->second.subscribers();
}

/*****************************************************************************
** Implementation for int type specialization
*****************************************************************************/

void SigSlotsManager<int>::printStatistics()
{
	std::cout << "Topics" << std::endl;
	std::map< std::string, Topic<int> >::iterator iter;
	for ( iter = topics().begin(); iter != topics().end(); ++iter ) {
		std::cout << iter->second;
	}
}

const SigSlotsManager<int>::Subscribers* SigSlotsManager<int>::connectSignal(const std::string& topic, SigSlot<int>* sigslot)
{
	// Try and insert a new topic in case it doesn't already exist
	// In any case, we always get the iterator back (to new or existing)
	//
	// Maybe improve the efficiency of this by specifying position
	// refer to http://www.cplusplus.com/reference/stl/map/insert/
	std::pair< std::map< std::string, Topic<int> >::iterator,bool> ret = topics().insert( std::pair< std::string, Topic<int> >(topic, Topic<int>(topic)) );
	Topic<int>& current_topic = (ret.first)->second;
	current_topic.addPublisher(sigslot);
	return current_topic.subscribers();
}

void SigSlotsManager<int>::connectSlot(const std::string& topic, SigSlot<int>* sigslot)
{
	// Try and insert a new topic in case it doesn't already exist
	// In any case, we always get the iterator back (to new or existing)
	//
	// Maybe improve the efficiency of this by specifying position
	// refer to http://www.cplusplus.com/reference/stl/map/insert/
	std::pair< std::map< std::string, Topic<int> >::iterator,bool> ret = topics().insert(std::pair< std::string, Topic<int> >(topic, Topic<int>(topic)) );
	Topic<int>& current_topic = (ret.first)->second;
	current_topic.addSubscriber(sigslot);
}

void SigSlotsManager<int>::disconnect(const std::string& topic, SigSlot<int>* sigslot)
{
	std::map<std::string, Topic<int> >::iterator iter = topics().find(topic);
	if ( iter != topics().end() ) {
		iter->second.disconnect(sigslot);
	}
	if ( iter->second.empty() ) {
		topics().erase(iter);
	}
}

bool SigSlotsManager<int>::isTopic(const std::string& topic)
{
	return !( topics().find(topic) == topics().end() );
}

std::map< std::string, Topic<int> >& SigSlotsManager<int>::topics()
{
	static std::map< std::string, Topic<int> > topic_list;
	return topic_list;
}

const SigSlotsManager<int>::Subscribers& SigSlotsManager<int>::subscribers(const std::string& topic)
{
	std::map< std::string, Topic<int> >::const_iterator iter = topics().find(topic);
	/*
	 * Note that this is called only by SigSlotsManager::connectSignal which
	 * makes sure the topic name exists, so we don't need to do any error
	 * handling here.
	 */
	// ecl_assert_throw( iter != topics().end(), StandardException(LOC,InvalidInputError,std::string("No sigslots topic with name:")+topic) );
	return *iter->second.subscribers();
}

/*****************************************************************************
** Implementation for float type specialization
*****************************************************************************/

void SigSlotsManager<float>::printStatistics()
{
	std::cout << "Topics" << std::endl;
	std::map< std::string, Topic<float> >::iterator iter;
	for ( iter = topics().begin(); iter != topics().end(); ++iter ) {
		std::cout << iter->second;
	}
}

const SigSlotsManager<float>::Subscribers* SigSlotsManager<float>::connectSignal(const std::string& topic, SigSlot<float>* sigslot)
{
	// Try and insert a new topic in case it doesn't already exist
	// In any case, we always get the iterator back (to new or existing)
	//
	// Maybe improve the efficiency of this by specifying position
	// refer to http://www.cplusplus.com/reference/stl/map/insert/
	std::pair< std::map< std::string, Topic<float> >::iterator,bool> ret = topics().insert( std::pair< std::string, Topic<float> >(topic, Topic<float>(topic)) );
	Topic<float>& current_topic = (ret.first)->second;
	current_topic.addPublisher(sigslot);
	return current_topic.subscribers();
}

void SigSlotsManager<float>::connectSlot(const std::string& topic, SigSlot<float>* sigslot)
{
	// Try and insert a new topic in case it doesn't already exist
	// In any case, we always get the iterator back (to new or existing)
	//
	// Maybe improve the efficiency of this by specifying position
	// refer to http://www.cplusplus.com/reference/stl/map/insert/
	std::pair< std::map< std::string, Topic<float> >::iterator,bool> ret = topics().insert(std::pair< std::string, Topic<float> >(topic, Topic<float>(topic)) );
	Topic<float>& current_topic = (ret.first)->second;
	current_topic.addSubscriber(sigslot);
}

void SigSlotsManager<float>::disconnect(const std::string& topic, SigSlot<float>* sigslot)
{
	std::map<std::string, Topic<float> >::iterator iter = topics().find(topic);
	if ( iter != topics().end() ) {
		iter->second.disconnect(sigslot);
	}
	if ( iter->second.empty() ) {
		topics().erase(iter);
	}
}

bool SigSlotsManager<float>::isTopic(const std::string& topic)
{
	return !( topics().find(topic) == topics().end() );
}

std::map< std::string, Topic<float> >& SigSlotsManager<float>::topics()
{
	static std::map< std::string, Topic<float> > topic_list;
	return topic_list;
}

const SigSlotsManager<float>::Subscribers& SigSlotsManager<float>::subscribers(const std::string& topic)
{
	std::map< std::string, Topic<float> >::const_iterator iter = topics().find(topic);
	/*
	 * Note that this is called only by SigSlotsManager::connectSignal which
	 * makes sure the topic name exists, so we don't need to do any error
	 * handling here.
	 */
	// ecl_assert_throw( iter != topics().end(), StandardException(LOC,InvalidInputError,std::string("No sigslots topic with name:")+topic) );
	return *iter->second.subscribers();
}

};

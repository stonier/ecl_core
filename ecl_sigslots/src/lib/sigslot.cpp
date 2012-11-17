/**
 * @file /ecl_sigslots/src/lib/sigslot.cpp
 *
 * @brief File comment
 *
 * File comment
 *
 * @date 13/05/2010
 **/

/*****************************************************************************
** Includes
*****************************************************************************/


#include "../../include/ecl/sigslots/sigslot.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Using
*****************************************************************************/

using std::map;
using std::set;
using std::string;
using ecl::Void;

/*****************************************************************************
** Implementation
*****************************************************************************/

SigSlot<Void>::~SigSlot() {
	disconnect(); // stop any new processing from connected signals
	mutex.lock(); // acts like a barrier - holds up here if function still processing stuff.
	delete function;
}

void SigSlot<Void>::emit() {
	PublicationMap::const_iterator topic_iter;
	Subscribers::const_iterator slots_iter;
	for ( topic_iter = publications.begin(); topic_iter != publications.end(); ++topic_iter ) {
		const Subscribers* subscribers = topic_iter->second;
		for ( slots_iter = subscribers->begin(); slots_iter != subscribers->end(); ++slots_iter ) {
			SigSlot *sigslot = *slots_iter;
			sigslot->process();
		}
	}
};

void SigSlot<Void>::process(Void void_arg) {
	mutex.trylock(); // Only lock if its not already locked.
	++processing_count;
	(*function)();
	if ( --processing_count == 0 ) {
		mutex.unlock();
	}

}

void SigSlot<Void>::connectSignal(const std::string& topic) {
	// Logic:
	//   - if already publishing to this topic
	//     - don't do anything
	//   - else
	//     - if topic doesn't exist
	//       - Manager will automatically create a new topic
	//     - Manager returns the subscribers handle
	//     - Topic name and subscribers handle are stored locally here in publications
	publications.insert( std::pair<std::string, const Subscribers*>(topic, SigSlotsManager<Void>::connectSignal(topic,this)) );
}

void SigSlot<Void>::connectSlot(const std::string& topic) {
	std::pair< set<std::string>::iterator,bool > ret;
	ret = subscriptions.insert(topic); // Doesn't matter if it already exists.
	if ( ret.second ) {
		SigSlotsManager<Void>::connectSlot(topic,this);
	} // else { already subscribed to this topic }
}
void SigSlot<Void>::disconnect(const std::string &topic) {
	set<std::string>::const_iterator listen_iter = subscriptions.find(topic);
	publications.erase(topic); // Doesn't matter if it finds it or not.
	SigSlotsManager<Void>::disconnect(topic,this);
}

void SigSlot<Void>::disconnect() {
	set<std::string>::iterator iter;
	for ( iter = subscriptions.begin(); iter != subscriptions.end(); ++iter ) {
		SigSlotsManager<Void>::disconnect(*iter, this);
	}
	subscriptions.clear();
	map<std::string,const Subscribers*>::iterator emit_iter;
	for ( emit_iter = publications.begin(); emit_iter != publications.end(); ++emit_iter ) {
		SigSlotsManager<Void>::disconnect(emit_iter->first, this);
	}
	publications.clear();
}

} // namespace ecl


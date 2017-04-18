#ifndef __9HACK_EVENT_H__
#define __9HACK_EVENT_H__

#include <unordered_set>

// Manages events with payload T.
// Order of callbacks is not maintained.
// It is reccommended to use struct/class payloads.
template <class T>
class Event {
  private:
    // The type definition for an event callback.
    typedef void (*cb_t)(T);

    // The internal vector of event callbacks.
    std::unordered_set<cb_t> callbacks;

  public:
    // Subscribes `cb` to this event.
    void subscribe(cb_t cb) {
      callbacks.insert(cb);
    }

    // Unsubscribes `cb` to this event.
    void unsubscribe(cb_t cb) {
      callbacks.erase(cb);
    }

    // Dispatches an event with payload `data`.
    void dispatch(T data) {
      for (cb_t cb : callbacks)
        (*cb)(data);
    }
};

#endif /* ifndef __9HACK_EVENT_H__ */

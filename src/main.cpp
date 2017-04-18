#include <iostream>
#include "event.hpp"

// Create a PositionData payload.
static struct PositionData {
  int x;
  int y;
};
// Create PositionChangeEvent which dispatches a paylaod of PositionData.
static auto PositionChangeEvent = Event<PositionData>();

// Create some callbacks which can subscribe to events with a
// PositionData payload.
static void p_print(PositionData p) {
  std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
}
static void b_print(PositionData p) {
  std::cout << "[" << p.x << ", " << p.y << "]" << std::endl;
}

int main() {
  // Subscribe our callbacks to PositionChangeEvent.
  PositionChangeEvent.subscribe(&p_print);
  PositionChangeEvent.subscribe(&b_print);

  // Dispatch a PositionChangeEvent with x = 0, y = 2
  // using designated initializer syntax.
  PositionChangeEvent.dispatch({
    .y = 2,
  });

  // Unsubscribe one of the callbacks, and dispatch another
  // PositionChangeEvent.
  PositionChangeEvent.unsubscribe(&b_print);
  PositionChangeEvent.dispatch({
    .x = 3,
    .y = 4,
  });

  return 0;
}

#include <iostream>
#include "events/event.h"

namespace kuuhaku {
namespace events {

// Create a PositionData payload.
struct PositionData {
  int x;
  int y;
};
// Create PositionChangeEvent which dispatches a paylaod of PositionData.
static Event<PositionData> PositionChangeEvent;

// Create some callbacks which can subscribe to events with a
// PositionData payload.
static void p_print(PositionData p) {
  std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
}
static void b_print(PositionData p) {
  std::cout << "[" << p.x << ", " << p.y << "]" << std::endl;
}

void example() {
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
}

}
}

int main() {
  kuuhaku::events::example();
  return 0;
}

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "event.hpp"
#include "object.hpp"

#include <painter_module/detail/ncurses_paint_engine.hpp>
#include <painter_module/paint_engine.hpp>
#include <painter_module/palette.hpp>

#include <aml/signals/slot.hpp>

#include <memory>

namespace twf {

class Widget;

class System : public Object {
   public:
    static void post_event(Object* obj,
                           std::unique_ptr<Event> event,
                           int priority = 0);
    static void remove_posted_event(Event* event);
    static bool send_event(Object* obj, const Event& event);
    static void send_posted_events(Object* obj_filter = nullptr,
                                   Event::Type etype_filter = Event::None);
    static bool notify(Object* obj, const Event& event);
    static void exit(int return_code = 0);
    static Object* head();
    static unsigned max_width();
    static unsigned max_height();
    static Paint_engine* paint_engine();
    static void set_paint_engine(std::unique_ptr<Paint_engine> engine);
    static Widget* focus_widget();
    static void set_focus_widget(Widget* widg);
    static void cycle_tab_focus();
    static void set_palette(std::unique_ptr<Palette> palette);
    static Palette* palette();

    explicit System(std::unique_ptr<Paint_engine> engine =
                        std::make_unique<detail::NCurses_paint_engine>());
    ~System() override;

    static void set_head(Object* obj);
    int run();

    // Slots
    sig::Slot<void()> quit = []() { System::exit(); };

    friend class Abstract_event_dispatcher;

   private:
    static Object* head_;
    static std::unique_ptr<Paint_engine> engine_;
    static Widget* focus_widg_;
    static std::unique_ptr<Palette> system_palette_;
    static bool notify_helper(Object* obj, const Event& event);
};

}  // namespace twf
#endif  // SYSTEM_HPP
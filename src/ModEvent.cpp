#include "ModEvent.h"
#include "WindowManager.h"

namespace {
    constexpr std::string_view kOpenEvent = "SKSEMenuFramework_Open"sv;
    constexpr std::string_view kCloseEvent = "SKSEMenuFramework_Close"sv;
    constexpr std::string_view kToggleEvent = "SKSEMenuFramework_Toggle"sv;

    class ModCallbackSink : public RE::BSTEventSink<SKSE::ModCallbackEvent> {
    public:
        static ModCallbackSink* GetSingleton() {
            static ModCallbackSink singleton;
            return &singleton;
        }

        RE::BSEventNotifyControl ProcessEvent(
            const SKSE::ModCallbackEvent* a_event,
            RE::BSTEventSource<SKSE::ModCallbackEvent>*) override {
            if (!a_event || !a_event->eventName.c_str()) {
                return RE::BSEventNotifyControl::kContinue;
            }

            const std::string_view name{a_event->eventName.c_str()};
            if (name == kOpenEvent) {
                WindowManager::Open();
            } else if (name == kCloseEvent) {
                WindowManager::Close();
            } else if (name == kToggleEvent) {
                if (WindowManager::MainInterface->IsOpen.load()) {
                    WindowManager::Close();
                } else {
                    WindowManager::Open();
                }
            }

            return RE::BSEventNotifyControl::kContinue;
        }

    private:
        ModCallbackSink() = default;
        ~ModCallbackSink() override = default;
        ModCallbackSink(const ModCallbackSink&) = delete;
        ModCallbackSink& operator=(const ModCallbackSink&) = delete;
    };
}

void ModEvent::Install() {
    auto* source = SKSE::GetModCallbackEventSource();
    if (!source) {
        logger::warn("Mod callback event source unavailable; open-by-event disabled");
        return;
    }

    source->AddEventSink(ModCallbackSink::GetSingleton());
    logger::info("Mod event listener installed ({}, {}, {})", kOpenEvent, kCloseEvent,
                 kToggleEvent);
}

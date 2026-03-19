namespace TactileTaskBoard {
    //implementations will change between versions, but the relationships will not
    class ITaskButton {
        public:
        virtual void Setup() = 0; //sets up the button so that it is ready to receive input
        virtual void AttachInterrupt() = 0;
        //TODO: events

        virtual ~ITaskButton() = default;
    };
        
    class ITaskLED {
        public:
        virtual void TurnOn() = 0;
        virtual void TurnOff() = 0;
        virtual void Toggle() = 0;
        virtual bool IsOn() = 0;
        virtual ~ITaskLED() = default;
    };

    
}

#include "./Settings.h"

class SaveManager
{
private:
public:
    SaveManager() {};
    void SaveData(const Settings &s);
    void LoadData(Settings &s);
};

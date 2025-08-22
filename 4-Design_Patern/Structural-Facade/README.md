- Facade cung cấp các interface cấp cao, giúp người dùng tương tác với thư viện cấp thấp 1 cách dễ dàng
- Các facade trong bài này gồm có:

```C
    void facade_activate_morning_routine(SmartHomeFacade* f, const SceneOptions* opt);
    void facade_activate_away_mode(SmartHomeFacade* f);
    void facade_set_movie_night_scene(SmartHomeFacade* f);

    void facade_set_room_brightness(SmartHomeFacade* f, const char* room, int pct);
    void facade_set_comfort_temp(SmartHomeFacade* f, float c);
```

- Bên trong các facade này sẽ implement code giao tiếp với các thư viện cấp thấp
#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

class Scene;

class SceneManager {
   private:
    static SceneManager* instance;

    Scene* currentScene;
    SceneManager();
    ~SceneManager();

   public:
    static SceneManager* getInstance();
    static void disposeInstance();

    Scene* getCurrentScene();

    void replaceScene(Scene* newScene);
    void startScene();
    void runSceneUpdate(double delta);
    void runSceneRender();
};

#endif

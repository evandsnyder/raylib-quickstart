#ifndef VERTEX_CONFIGURATION_HPP
#define VERTEX_CONFIGURATION_HPP

namespace vertex {
	class Configuration {
	public:
		static Configuration& Get();

		Configuration(const Configuration&) = delete;
		void operator=(const Configuration&) = delete;

		void SetScreenWidth(float NewScreenWidth);
		float GetScreenWidth() const;
		void SetScreenHeight(float NewScreenHeight);
		float GetScreenHeight() const;

	private:
		Configuration();


		float ScreenWidth = 800;
		float ScreenHeight = 450;
	};
}

#endif

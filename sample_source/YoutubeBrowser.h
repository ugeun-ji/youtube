#pragma once

class JSObject;
class WebformDispatchImpl;
class WebWindow;

namespace Web
{
	struct YouTubePlayerState
	{
		enum Enums
		{
			PreStart,
			Stop,
			Play,
			Pause,
			MaxCount,
		};
	};

	struct IYouTubeBrowserCallback
	{
		virtual ~IYouTubeBrowserCallback() = default;

		virtual void OnPreStartVideo()					{}
		virtual void OnPlayVideo()						{}
		virtual void OnPauseVideo()						{}
		virtual void OnStopVideo()						{}
		virtual void OnVideoHTML5Error()				{}
		virtual void OnFullscreenModeChanged(bool ok)	{}
		virtual void OnShow(bool ok)					{}
		virtual void OnVideoReady(const i3::string& videoKeys, bool isWebEnable) {}
	};	

	class YoutubeBrowser
	{
	public:
		YoutubeBrowser();
		~YoutubeBrowser();

		bool Go(const i3::string& url);
		bool Refresh();
		void MoveWindow(const i3::pack::RECT& rt);
		void Show(bool ok);

		bool IsWebEnable() const;
		bool IsFullScreenMode() const;
		bool IsInternetExplorerEnable() const;

		void SetCallback(IYouTubeBrowserCallback* callback);

		const i3::pack::RECT& GetCurrWindowRect() const;

		void PlayNone();
		void PlayVideo();
		void PauseVideo();
		void StopVideo();

		void OnPreStartVideo(const i3::vector<i3::string>& args);
		void OnPlayVideo(const i3::vector<i3::string>& args);
		void OnPauseVideo(const i3::vector<i3::string>& args);
		void OnStopVideo(const i3::vector<i3::string>& args);
		void OnFullscreenModeChanged(const i3::vector<i3::string>& args);
		void OnVideoHTML5Error(const i3::vector<i3::string>& args);
		void OnVideoReady(const i3::vector<i3::string>& args);

	private:
		JSObject* m_jsobj = nullptr;
		WebformDispatchImpl* m_webformDispImpl = nullptr;
		WebWindow* m_webWindow = nullptr;
		bool m_show = false;
		bool m_isWebEnable = false;
		bool m_isFullScreenMode = false;
		bool m_isInternetExplorerEnable = false;

		YouTubePlayerState::Enums m_videoPlayState = YouTubePlayerState::PreStart;
		i3::function<void()> m_videoShowCallback;

		IYouTubeBrowserCallback* m_callback = nullptr;
		i3::pack::RECT m_rect;
	};

	bool CheckPossibleIEVersionOfYouTube();

	struct YouTubeTimerEvent
	{
		REAL32 time = -1.0f;
		i3::function<void()> event;

		YouTubeTimerEvent();
		YouTubeTimerEvent(REAL32 tm, i3::function<void()> evt);
	};

	class IYouTubeTimer
	{
	public:
		IYouTubeTimer() = default;
		virtual ~IYouTubeTimer() = default;

		virtual void Start()				{}
		virtual void Stop()					{}
		virtual void OnUpdate(REAL32 tm)	{}
		virtual void SetEvent(YouTubeTimerEvent evt) {}
		virtual REAL32 GetCurrTm() const	{ return 0.0f;  }
	};

	class YouTubeTimerNone : public IYouTubeTimer
	{
	public:
		virtual ~YouTubeTimerNone() = default;
	};

	class YouTubeTimer : public IYouTubeTimer
	{
	public:
		YouTubeTimer() = default;
		virtual ~YouTubeTimer() = default;

		virtual void Start() override;
		virtual void Stop() override;
		virtual void OnUpdate(REAL32 tm) override;
		virtual void SetEvent(YouTubeTimerEvent evt) override;
		virtual REAL32 GetCurrTm() const override;

	private:
		bool m_stopOK = true;
		REAL32 m_tm = 0.0f;
		YouTubeTimerEvent m_event;
	};
}


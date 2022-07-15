#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <windows.h>
#include <ctime>
#include "discord-files/discord.h"

const discord::ClientId clientId = 996539052255871118;

struct DiscordState {
	std::unique_ptr<discord::Core> core;
};

discord::Activity activity{};

struct Tab {
	std::string path;
	std::string title;
};

Tab lastTab;
Tab currTab;

Tab getCurrentTab()
{
	std::ifstream currTabStream("../../current-tab.txt");

	std::string tab;
	std::stringstream buff;
	buff << currTabStream.rdbuf();
	tab = buff.str();

	size_t newlinePos = tab.find_first_of('\n');
	currTab.path = tab.substr(0, newlinePos);
	currTab.title = tab.substr(newlinePos + 1, tab.size() - newlinePos - 1);

	return currTab;
}


int main()
{
	FreeConsole();
	srand(1LL * time(NULL) % 5 * time(NULL) % SHRT_MAX * time(NULL) % INT_MAX * (time(NULL) - 10));

	DiscordState state{};
	discord::Core* core{};
	auto response = discord::Core::Create(clientId, DiscordCreateFlags_NoRequireDiscord, &core);
	state.core.reset(core);

	while (!state.core) {
		std::cout << "Failed to instantiate Discord! Retrying...\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(4000));
		response = discord::Core::Create(clientId, DiscordCreateFlags_NoRequireDiscord, &core);
		state.core.reset(core);
	}

	activity.SetDetails("/profil/ezluci");
	activity.GetAssets().SetLargeImage("copil-color");
	activity.GetAssets().SetLargeText("copil-color");
	activity.GetTimestamps().SetStart(time(NULL) - rand() % 40000);
	state.core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
		std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed") << " updating activity!\n";
	});

	do {
		getCurrentTab();

		if (currTab.path != lastTab.path)
		{
			int probId = 0;
			std::string probName;

			if (currTab.path.size() >= 11 && currTab.path.substr(0, 10) == "/probleme/" &&
				currTab.title.find_first_of('|') != std::string::npos)
			{
				probName = currTab.title.substr(9, currTab.title.find_first_of('|', 9) - 10);

				for (int i = 10; i <= 13 && isdigit(currTab.path[i]); ++i)
					probId = probId * 10 + currTab.path[i] - '0';
			}


			std::string text = "Now: " + (probId == 0 ? "Nothing" : probName + " #" + std::to_string(probId));
			activity.SetState(text.c_str());
			state.core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
				std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed") << " updating activity!\n";
			});
			lastTab = currTab;
		}

		state.core->RunCallbacks();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	} while (true);
}
#include "imguiHelper/ImguiAssetBrowser.h"
#include "vulkanTools/vulkanInstance.h"
#include <string>

namespace TDS
{
	AssetBrowser::AssetBrowser()
	{
		//selected = 0;
		//selectedFolder = -1;
		//renameCheck = false;

		flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		panelTitle = "Asset Browser";
		windowPadding = ImVec2(0.f, 0.f);
		m_curr_path = "../assets";

		//insertEntities();
	}

	void AssetBrowser::getFileNameFromPath(const char* full_path, std::string* path, std::string* file, std::string* fileWithExtension, std::string* extension) const
	{
		if (full_path != nullptr)
		{
			std::string nwFullPath = full_path;
			std::string& full_path_ = nwFullPath;
			//bool toLower;
			for (std::string::iterator charIterator = full_path_.begin(); charIterator != full_path_.end(); ++charIterator)
			{
				if (*charIterator == '\\')
					*charIterator = '/';
				/*else
					if (toLower) {
						*charIterator = tolower(*charIterator);
					}*/
			}
			size_t posSlash = nwFullPath.find_last_of("\\/");
			size_t posDot = nwFullPath.find_last_of(".");

			if (path != nullptr)
			{
				if (posSlash < nwFullPath.length())
					*path = nwFullPath.substr(0, posSlash + 1);
				else
					path->clear();
			}
			if (fileWithExtension != nullptr) {
				if (posSlash < nwFullPath.length()) {
					*fileWithExtension = nwFullPath.substr(posSlash + 1);
				}
				else
					*fileWithExtension = nwFullPath;
			}

			if (file != nullptr)
			{
				nwFullPath = nwFullPath.substr(0, posDot);
				posSlash = nwFullPath.find_last_of("\\/");
				*file = nwFullPath.substr(posSlash + 1);

			}

			if (extension != nullptr)
			{
				if (posDot < nwFullPath.length())
					*extension = nwFullPath.substr(posDot);
				else
					extension->clear();
			}
		}
	}

	static const std::filesystem::path s_TextureDirectory = "assets/";
	void AssetBrowser::update()
	{
		if (m_curr_path != std::filesystem::path(s_TextureDirectory))
		{
			if (ImGui::Button("<-")) //will only show if u went into a folder in the current directory above
			{
				m_curr_path = m_curr_path.parent_path();
			}
		}
		//float cellSize = thumbnail_size + padding;

		//float panelWidth = ImGui::GetContentRegionAvail().x;
		//float columnCount = (int)(panelWidth / cellSize);
		ImGui::Columns(4, 0, false);

		for (auto& directory_entry : std::filesystem::directory_iterator(m_curr_path))
		{
			path1 = directory_entry.path().string();
			auto relative_path = std::filesystem::relative(directory_entry.path(), s_TextureDirectory);

			//ImGui::Button(path1.c_str(), { thumbnail_size, thumbnail_size });
			//shorten the path name
			std::string filename;
			getFileNameFromPath(path1.c_str(), nullptr, nullptr, &filename, nullptr);



			ImGui::Button(filename.c_str(), { thumbnail_size, thumbnail_size });
			
			if (ImGui::IsItemClicked(0))
			{
				
				//if it has a "." in it, it is a file, do not add to path
				//only directories/folders can be added to path

				//if it is a folder, open it and update the asset broswer curr dir
				if (!strstr(filename.c_str(), ".")) 
				{
					m_curr_path += "/" + filename;
				

					//attempt at drag drop
					selectedpath = path1;
					

				}
				//use the rest of the checks below to handle what happens when u press different kinds of file extensions

				//if .jpg/.PNG, load 2d texture...
				if (strstr(filename.c_str(), ".jpg")|| strstr(filename.c_str(), ".png"))
				{

				}
				//if .json, load scene...
				if (strstr(filename.c_str(), ".json"))
				{

				}
				//if .dds, do something...
				if (strstr(filename.c_str(), ".dds"))
				{

				}
				//if .wav, play audio...
				if (strstr(filename.c_str(), ".wav"))
				{

				}


			}
			ImGui::Text(filename.c_str());
			
			/*if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceExtern))
			{
				ImGui::SetDragDropPayload("path", path1.c_str(), 1);
				ImGui::Text(path1.c_str());
				if (!ImGui::IsMouseDown(0))
				{
					ImGui::EndDragDropSource();

				}
			}

			if (ImGui::BeginDragDropTarget())
			{
				ImGui::EndDragDropTarget();
			}*/
			ImGui::NextColumn();
		}


		ImGui::Columns(1);
		ImGui::SliderFloat("Thumbnail Size", &thumbnail_size, 16, 512);
		//ImGui::SliderFloat("Padding", &padding, 0, 32);


	}
}
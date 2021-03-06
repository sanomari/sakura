/*! @file */
/*
	Copyright (C) 2018-2021 Sakura Editor Organization

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

		1. The origin of this software must not be misrepresented;
		   you must not claim that you wrote the original software.
		   If you use this software in a product, an acknowledgment
		   in the product documentation would be appreciated but is
		   not required.

		2. Altered source versions must be plainly marked as such,
		   and must not be misrepresented as being the original software.

		3. This notice may not be removed or altered from any source
		   distribution.
*/
#include <comdef.h>

#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "_main/CCommandLine.h"

class CProfileManager
{
	std::vector<std::wstring> m_vProfiles;
	int m_nDefaultIndex;
	std::wstring m_szDllLanguage;

public:
	CProfileManager();
	virtual ~CProfileManager() = default;

	//! コマンドラインだけでプロファイルが確定するか調べる
	bool TrySelectProfile(CCommandLine* pcCommandLine) noexcept;
	[[nodiscard]] bool IsProfileNameValid(std::wstring_view name) const noexcept;
	[[nodiscard]] bool IsNewProfileName(std::wstring_view name) const noexcept;

	void Add(int index, std::wstring_view name);
	void Rename(int index, std::wstring_view name);
	void Delete(int index);
	void SetDefault(int index);
	void ClearDefault();
	void SetLanguageDll(const std::filesystem::path& languageDll) { m_szDllLanguage = languageDll; }

	[[nodiscard]] int GetSize() const noexcept;
	[[nodiscard]] std::wstring GetAt(int index) const;
	[[nodiscard]] std::optional<int> GetDefault() const noexcept;
	[[nodiscard]] std::filesystem::path GetLanguageDll() const { return m_szDllLanguage; }

	bool ReadSettings();
	bool WriteSettings() const;

private:
	void ValidateProfileName(std::wstring_view name) const;;
	bool IOProfSettings(bool bWrite);
};

std::filesystem::path GetProfileMgrFileName();
std::filesystem::path GetProfileDirectory(const std::wstring& name);

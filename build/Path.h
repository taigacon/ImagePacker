#pragma once

#include <string>
class Path
{
public:
	/**
	 *	路径combine
	 */
	static std::wstring combine(const std::wstring& path, const std::wstring& path2);
	static std::wstring combine(const std::wstring& path, std::wstring&& path2);
	static std::wstring combine(std::wstring&& path, std::wstring&& path2);
	static std::wstring combine(std::wstring&& path, const std::wstring& path2);
	/**
	 *	末尾添加名称分隔符（'/'）
	 */
	static std::wstring addSeparator(const std::wstring& path);
	static std::wstring addSeparator(std::wstring&& path);

	static std::wstring relativeToSimple(const std::wstring& path, const std::wstring& parent);
	static std::wstring relativeToSimple(std::wstring&& path, const std::wstring& parent);

	static constexpr wchar_t separator = L'/';
	static std::wstring normalize(const std::wstring& str);
	static std::wstring normalize(std::wstring&& str);

	static std::wstring changeExtension(const std::wstring& path, const std::wstring& extension);
	static std::wstring changeExtension(std::wstring&& path, const std::wstring& extension);
	static std::wstring removeExtension(std::wstring&& path);
	//返回目录名（包括/），假定输入路径已normalized
	static std::wstring_view getDirectory(const std::wstring_view& path);
	static std::wstring_view getParentDirectory(const std::wstring_view& path);
	static std::wstring_view getExtension(const std::wstring_view& path);
	static std::wstring_view getFullExtension(const std::wstring_view& path);
	static std::wstring_view getExtensionFromFileName(const std::wstring_view& filename);
	static std::wstring_view getFullExtensionFromFileName(const std::wstring_view& filename);
	static std::wstring_view getFileName(const std::wstring_view& path);
	static std::wstring_view getFileNameWithoutExtension(const std::wstring_view& path);
	static std::wstring_view getPathWithoutExtension(const std::wstring_view& path);
	static bool isMultiExtension(const std::wstring_view& ext);
	static std::wstring_view getFirstOfFullExtension(const std::wstring_view& fullExt);
	static std::wstring_view getTagExtension(const std::wstring_view& path);
	static std::wstring_view getTagExtensionFromFileName(const std::wstring_view& filename);
};

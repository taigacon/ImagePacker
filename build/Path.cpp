#include "Path.h"

std::wstring Path::combine(const std::wstring &path, const std::wstring &path2)
{
	if (path.back() != L'/')
	{
		return path + separator + path2;
	}
	return path + path2;
}

std::wstring Path::combine(const std::wstring& path, std::wstring&& path2)
{
	if (path.back() != L'/')
	{
		return path + separator + path2;
	}
	return path + path2;
}

std::wstring Path::combine(std::wstring&& path, std::wstring&& path2)
{
	if (path.back() != L'/')
	{
		return path + separator + path2;
	}
	return path + path2;
}

std::wstring Path::combine(std::wstring&& path, const std::wstring& path2)
{
	if (path.back() != L'/')
	{
		return path + separator + path2;
	}
	return path + path2;
}

std::wstring Path::addSeparator(const std::wstring &path)
{
	if (path.back() != L'/')
	{
		return path + separator;
	}
	return path;
}

std::wstring Path::addSeparator(std::wstring &&path)
{
	if (path.back() != L'/')
	{
		return path + separator;
	}
	return std::move(path);
}

std::wstring Path::relativeToSimple(const std::wstring &path, const std::wstring &parent)
{
	if (parent.empty())
	{
		return path;
	}
	if (parent.back()=='/' || parent.back()=='\\')
	{
		return path.substr(parent.size());
	}
	return path.substr(parent.size() + 1);
}

std::wstring Path::relativeToSimple(std::wstring&& path, const std::wstring& parent)
{
	if (parent.empty())
	{
		return std::move(path);
	}
	if (parent.back() == '/' || parent.back() == '\\')
	{
		path.erase(0, parent.size());
	}
	else
	{
		path.erase(0, parent.size() + 1);
	}
	return std::move(path);
}

std::wstring Path::normalize(const std::wstring &str)
{
	std::wstring rtn;
	const wchar_t *cur = &str[0], *end = cur + str.size();
	while (cur < end)
	{
		if (*cur != L'/' && *cur != L'\\')
		{
			rtn.push_back(*cur);
			cur++;
			continue;
		}
		rtn.push_back(L'/');
		do { cur++; } while (*cur == L'\\' || *cur == L'/');
	}
	return std::move(rtn);
}

std::wstring Path::normalize(std::wstring&& str)
{
	int rpos = 0;
	int wpos = 0;
	for (; rpos < str.size(); )
	{
		if(str[rpos] == L'/' || str[rpos] == L'\\')
		{
			str[wpos++] = L'/';
			do { rpos++; } while (str[rpos] == L'\\' || str[rpos] == L'/');
		}
		else
		{
			if(rpos != wpos)
			{
				str[wpos] = str[rpos];
			}
			rpos++;
			wpos++;
		}
	}
	if(rpos != wpos)
	{
		str.erase(wpos);
	}
	return std::move(str);
}

std::wstring Path::removeExtension(std::wstring&& path)
{
	std::wstring_view ext = getExtension(path);
	if (ext.empty())
		return std::move(path);
	path.erase(path.size() - ext.size());
	return std::move(path);
}

std::wstring_view Path::getDirectory(const std::wstring_view &path)
{
	auto pos = path.find_last_of(L'/');
	if (pos != std::wstring_view::npos)
	{
		return path.substr(0, pos + 1);
	}
	return std::wstring_view();
}

std::wstring_view Path::getParentDirectory(const std::wstring_view &path)
{
	if (path.size() <= 1)
		return std::wstring_view();
	auto pos = path.find_last_of(L'/', path.size()-1);
	if (pos != std::wstring_view::npos)
	{
		return path.substr(0, pos + 1);
	}
	return std::wstring_view();
}

std::wstring_view Path::getExtension(const std::wstring_view &path)
{
	return getExtensionFromFileName(getFileName(path));
}

std::wstring_view Path::getFullExtension(const std::wstring_view& path)
{
	return getFullExtensionFromFileName(getFileName(path));
}

std::wstring_view Path::getExtensionFromFileName(const std::wstring_view &filename)
{
	auto pos = filename.find_last_of(L'.');
	if (pos != std::wstring_view::npos)
	{
		return filename.substr(pos);
	}
	return std::wstring_view();
}

std::wstring_view Path::getFullExtensionFromFileName(const std::wstring_view& filename)
{
	auto pos = filename.find_first_of(L'.');
	if (pos != std::wstring_view::npos)
	{
		return filename.substr(pos);
	}
	return std::wstring_view();
}

std::wstring_view Path::getFileName(const std::wstring_view &path)
{
	auto pos = path.find_last_of(L"/\\");
	if (pos != std::wstring_view::npos)
	{
		return path.substr(pos + 1);
	}
	return path;
}

std::wstring_view Path::getFileNameWithoutExtension(const std::wstring_view &path)
{
	std::wstring_view filename = getFileName(path);
	auto pos = filename.find_first_of(L'.');
	if (pos != std::wstring_view::npos)
	{
		return filename.substr(0, pos);
	}
	return std::wstring_view();
}

std::wstring_view Path::getPathWithoutExtension(const std::wstring_view& path)
{
	std::wstring_view fullExt = Path::getFullExtension(path);
	if (fullExt.empty())
		return path;
	return path.substr(0, path.size() - fullExt.size());
}

bool Path::isMultiExtension(const std::wstring_view& ext)
{
	auto pos = ext.find_first_of(L'.');
	if (pos == std::wstring_view::npos)
		return false;
	pos = ext.find_first_of(L'.', pos + 1);
	return pos != std::wstring_view::npos;
}

std::wstring_view Path::getFirstOfFullExtension(const std::wstring_view& fullExt)
{
	auto pos = fullExt.find_first_of(L'.');
	if (pos == std::wstring_view::npos)
		return std::wstring_view();
	auto secondPos = fullExt.find_first_of(L'.', pos + 1);
	if (secondPos == std::wstring_view::npos)
		return fullExt;
	return fullExt.substr(pos, secondPos - pos);
}

std::wstring_view Path::getTagExtension(const std::wstring_view& path)
{
	return getTagExtensionFromFileName(getFileName(path));
}

std::wstring_view Path::getTagExtensionFromFileName(const std::wstring_view& filename)
{
	std::wstring_view fullExt = getFullExtensionFromFileName(filename);
	if(isMultiExtension(fullExt))
	{
		return getFirstOfFullExtension(fullExt);
	}
	return std::wstring_view();
}


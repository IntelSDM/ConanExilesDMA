#pragma once
// ScriptStruct CoreUObject.Vector
struct UEVector {
	float X; // 0x0(0x4)
	float Y; // 0x40x4)
	float Z; // 0x8(0x4)
};
// ScriptStruct CoreUObject.Rotator
struct UERotator {
	float Pitch; // 0x0(0x4)
	float Yaw; // 0x4(0x4)
	float Roll; // 0x8(0x4)
};
struct MinimalViewInfo
{
	struct UEVector Location; // 0x0(0xC)
	struct UERotator Rotation; // 0xC(0xC)
	float FOV; // 0x18(0x4)
};
struct CameraCacheEntry
{
	float Timestamp; // 0x00(0x04)
	char pad_4[0xc]; // 0x04(0x0c)
	MinimalViewInfo POV; // 0x10(0x5e0)
};

template <class T>
class TArray
{
public:
    int Length() const
    {
        return m_nCount;
    }

    bool IsValid() const
    {
        if (m_nCount > m_nMax)
            return false;
        if (!m_Data)
            return false;
        return true;
    }

    uint64_t GetAddress() const
    {
        return m_Data;
    }

    uintptr_t GetPtrAddress(int i)
    {
        return m_Data + i * 8;
    }

protected:
    uint64_t m_Data;
    uint32_t m_nCount;
    uint32_t m_nMax;
};

struct FakeTarray
{
    uint64_t m_Data;
    uint32_t m_nCount;
    uint32_t m_nMax;
};

struct FString : private TArray<wchar_t>
{
    wchar_t* buffer;
    std::wstring str;

    std::wstring ToWString()
    {
        wchar_t* buffer = new wchar_t[m_nCount + 1];
        TargetProcess.Read(m_Data, buffer, m_nCount * sizeof(wchar_t));
        std::wstring ws(buffer);
        delete[] buffer;

        return ws;
    }

    void QueueString(VMMDLL_SCATTER_HANDLE handle)
    {
        buffer = new wchar_t[m_nCount + 1];
        TargetProcess.AddScatterReadRequest(handle, m_Data, buffer, m_nCount * sizeof(wchar_t));
    }

    std::wstring GetWString()
    {
        if (!str.empty())
            return str;

        std::wstring ws(buffer);
        delete[] buffer;
        return ws;
    }

    std::string ToString()
    {
        std::wstring ws = ToWString();
        std::string str(ws.begin(), ws.end());

        return str;
    }
};

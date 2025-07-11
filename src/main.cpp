#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

// 函數用於從 /proc/meminfo 讀取並解析記憶體資訊
void getMemoryInfo(){
	// 嘗試打開 /proc/meminfo 文件
	//宣告一個型別為 std::ifstream 的變數，並將其命名為 meminfo_file的物件。
	//"/proc/meminfo"是傳遞給 std::ifstream 建構子 (constructor) 的參數。
	//建構子是類別中的一個特殊成員函數，用於在創建物件時初始化它。
	//在這裡，它接收一個字串參數，這個字串就是您想要打開的檔案的路徑和名稱。
	//"/proc/meminfo" 就是 Linux 系統中一個特殊的虛擬檔案的路徑，它包含了系統的記憶體資訊。當 meminfo_file 物件被創建時，它會立即嘗試打開這個指定的檔案。
	//因此，std::ifstream meminfo_file("/proc/meminfo"); 這句話的含義就是：
	//「建立一個名為 meminfo_file 的輸入檔案流物件，並嘗試打開 /proc/meminfo 這個檔案，以便從中讀取數據。」
	std::ifstream meminfo_file("/proc/meminfo");
	// 檢查文件是否成功打開
	if (!meminfo_file.is_open()){
		std::cerr << "Error: Could not open /proc/meminfo" << std::endl;
		return;
	}

	//聲明一個字串變數，用於儲存從文件中讀取到的每一行內容
	std::string line;
	//聲明一個 std::map，用於儲存解析後的記憶體資訊。
	//std::map 是一種關聯容器 (Associative Container)，它儲存的是由鍵 (key) 和值 (value) 組成的鍵值對 (key-value pairs)。
	//鍵 (key) 是記憶體項目的名稱 (如 "MemTotal")，值 (value) 是對應的記憶體大小 (long 型別)。
	//自動排序: std::map 中的所有元素都會根據鍵的順序自動排序。這使得按照鍵來查找元素非常高效
	//唯一鍵: 每個鍵在 std::map 中都是唯一的。如果你嘗試插入一個已經存在的鍵，它會更新該鍵對應的值，而不是創建一個新的條目。
	//動態大小: std::map 可以根據需要動態地增加或減少其大小。
	//<std::string, long>是 std::map 的模板參數 (Template Parameters)。
	//std::map 是一個模板類別，這意味著它可以用來儲存任何型別的鍵和值。你需要在 <> 中指定鍵和值的具體型別。
	//std::string: 這是第一個模板參數，表示 std::map 中儲存的鍵 (key) 的型別將會是 std::string。
	//long: 這是第二個模板參數，表示 std::map 中儲存的值 (value) 的型別將會是 long。long 是一個整數型別，通常用於儲存較大的整數值。
	//例如讀到 MemTotal:       16431208 kB，程式就會將 "MemTotal" 作為鍵，16431208 作為值，儲存到 mem_values 這個 std::map 中：
	//mem_values["MemTotal"] = 16431208;
	std::map<std::string, long> mem_values;
	//循環讀取文件中的每一行，直到文件結束 (EOF) 或讀取失敗
	//std::getline()是一個定義在 <string> 標頭檔中的函數，用於從輸入流中讀取一行文本。
	//它接受兩個主要參數：
	//1.meminfo_file (第一個參數)：這是一個 std::ifstream 物件，代表我們要從中讀取的輸入流（也就是 /proc/meminfo 這個文件）。
	//2.line (第二個參數)：這是一個 std::string 物件，
	//std::getline() 會將從輸入流中讀取到的那一整行內容（包括空格，直到遇到換行符或文件結束）儲存到這個 line 變數中。
	//std::getline() 的返回值：這個函數會返回它接收的第一個參數（也就是 meminfo_file 物件自身的引用）。
	//作為 while 循環的條件： 當 std::ifstream 物件 (例如 meminfo_file) 被用作布林上下文 (boolean context) 時（例如在 if 或 while 條件中），它會檢查流的狀態：
	//  如果成功讀取了一行並且沒有遇到文件結束符 (EOF) 或其他錯誤，那麼流的狀態是「良好」的，此時轉換為 true。
	//  如果讀取失敗（例如文件已經讀到末尾，或者發生了其他 I/O 錯誤），那麼流的狀態會變為「錯誤」或「文件結束」，此時轉換為 false。
	//總結第一行： 這行程式碼的意思是「不斷地從 meminfo_file 中讀取一行內容，並將其儲存到 line 變數中，只要還能成功讀取到一行，就繼續循環。」
	while (std::getline(meminfo_file, line)) {
		//創建一個 stringstream 對象，將當前行 (line) 的內容載入其中
		//stringstream 允許您像操作文件流一樣操作字串，方便解析
		//這行程式碼的作用是為剛讀取到的一行文本準備進一步的解析。
		//std::stringstream：
		//  -這是一個定義在 <sstream> 標頭檔中的類別。
		//  -它是一個字串流 (string stream)。你可以把它想像成一個介於文件流 (ifstream) 和字串 (string) 之間的橋樑。
		//  -它允許您像操作文件輸入/輸出流 (std::cin, std::cout, std::ifstream, std::ofstream) 一樣，
		//  對字串進行輸入 (>>) 和輸出 (<<) 操作。這對於從一行複雜的字串中提取多個不同型別的數據非常方便。
		//ss:
		//  -這是您為 std::stringstream 物件所取的名稱。
		//(line)：
		//  -這部分是傳遞給 std::stringstream 建構子 (constructor) 的參數。
		//  當您這樣初始化 std::stringstream 時，它會將 line 變數中的所有內容作為其內部的「字串緩衝區」。
		//  從此以後，您對 ss 物件進行的任何讀取操作，都將是從這個 line 的內容中讀取。
		//  現在，ss 就變成了一個可以像讀取 std::cin 或 std::ifstream 那樣進行操作的流，您可以從中提取 key、value 和 unit 等部分，
		//  而無需直接處理字串的複雜解析（例如查找子字串、轉換數據型別等）。
		//  例如，接下來的 std::getline(ss, key, ':') 和 ss >> value >> unit; 就是利用了 ss 這個字串流的特性來完成解析。
		//  這種模式在 C++ 中非常常見，特別是在處理需要逐行讀取文件，然後再對每行內容進行結構化解析的場景。
		std::stringstream ss(line);
		//聲明一個字串變數，用於儲存解析出的記憶體項目的鍵 (Key)
		std::string key;
		//聲明一個 long 型別變數，用於儲存解析出的記憶體數值 (Value)
		long value;
		//聲明一個字串變數，用於儲存記憶體單位的字串 (通常是 "kB")
		std::string unit;
		//嘗試從 stringstream (ss) 中讀取內容，直到遇到冒號 (':')。
		//讀取到的內容會儲存在 key 變數中。
		//這個條件判斷確保了該行有冒號，符合 "Key: Value Unit" 的格式
		if (std::getline(ss, key, ':')) {
			//從 stringstream 物件 ss 中讀取數據，並將它們儲存到 value 和 unit 這兩個變數中。。
			//它利用了 C++ 流提取運算子 (stream extraction operator) >> 的特性。
			//ss: 這是您的 std::stringstream 物件。在執行到這行之前，ss 中可能還剩餘類似        16431208 kB 這樣的字串內容
			//（因為冒號 : 之前的鍵已經被 std::getline(ss, key, ':') 提取掉了）。
			//>> (流提取運算子):
			//  -這個運算子用於從輸入流中提取數據。
			//  -它的行為會根據目標變數的型別而定：
			//    -跳過空白字元: 當讀取數字或字串時，>> 運算子會自動跳過開頭的任何空白字元（例如空格、Tab 鍵、換行符等）。
			//    -讀取到下一個空白字元: 它會從流中讀取非空白字元，直到遇到下一個空白字元或流的末尾。
			//value: 這是一個 long 型別的變數。
			//  -當 ss >> value 執行時，stringstream ss 會嘗試從其內部緩衝區中讀取一個可以被解析為 long 型別的數字。
			//  -在我們的例子中，它會讀取 16431208 這個數字，並將其轉換為 long 型別後儲存到 value 變數中。
			//  -在讀取完 16431208 後，ss 的內部位置會移動到 kB 前面的空格。
			//unit: 這是一個 std::string 型別的變數。
			//  -緊接著 ss >> value 之後，ss >> unit 會執行。
			//  -stringstream ss 會自動跳過 16431208 後面的所有空白字元，然後讀取下一個非空白字元序列，直到遇到下一個空白字元或流的末尾。
			//  -在我們的例子中，它會讀取 kB 這個字串，並將其儲存到 unit 變數中。
			//  -讀取完 kB 後，ss 中已經沒有更多的內容了。
			//舉例說明：
			//  假設 line 變數在經過 std::getline(ss, key, ':') 處理後，ss 中剩餘的內容是："       16431208 kB"
			//  當執行 ss >> value >> unit; 時：
			//  ss >> value:
			//    -ss 會跳過開頭的空格。
			//    -讀取 16431208。
			//    -將 16431208 轉換為 long 型別並賦值給 value。
			//    -ss 內部現在指向  kB。
			//  ss >> unit:
			//    -ss 會跳過 16431208 和 kB 之間的空格。
			//    -讀取 kB。
			//    -將 kB 儲存為 std::string 型別並賦值給 unit。
			//    -ss 內部現在指向末尾。
			//所以，ss >> value >> unit; 這行程式碼的簡潔之處在於，它利用了流提取運算子的特性，可以一次性按順序從流中提取多個不同型別的數據，
			//並且會自動處理數據之間的分隔空白字元。
			ss >> value >> unit;
			//移除 key 字串開頭的空格和 Tab 字符。
			//`find_first_not_of(" \t")` 找到第一個非空格/非Tab字符的位置。
			//`erase(0, ...)` 從開頭刪除到該位置之前的所有字符。
			key.erase(0, key.find_first_not_of(" \t"));
			//移除 key 字串末尾的空格和 Tab 字符。
			//`find_last_not_of(" \t")` 找到最後一個非空格/非Tab字符的位置。
			//`+ 1` 是因為 erase 的第二個參數是數量，而不是結束位置。
			//這確保了鍵是乾淨的，例如 "MemTotal" 而不是 "MemTotal "。
			key.erase(key.find_last_not_of(" \t") + 1);
			//將解析出的鍵 (key) 和值 (value) 儲存到 mem_values 這個 map 中。
			mem_values[key] = value;
		}
	}
	meminfo_file.close();
	// 輸出我們關心的資訊
	std::cout << "Memory Information:" << std::endl;
	if (mem_values.count("MemTotal")) {
		std::cout << "  Total Memory: " << mem_values["MemTotal"] << " kB" << std::endl;
	}
	if (mem_values.count("MemFree")) {
		std::cout << "  Free Memory:  " << mem_values["MemFree"] << " kB" << std::endl;
	}
	if (mem_values.count("MemAvailable")) { // MemAvailable 是更準確的可用記憶體指標
		std::cout << "  Available Memory: " << mem_values["MemAvailable"] << " kB" << std::endl;
	}
	if (mem_values.count("Buffers")) {
		std::cout << "  Buffers:      " << mem_values["Buffers"] << " kB" << std::endl;
	}
	if (mem_values.count("Cached")) {
		std::cout << "  Cached:       " << mem_values["Cached"] << " kB" << std::endl;
	}

}









int main(){
	getMemoryInfo();
	return 0;
}


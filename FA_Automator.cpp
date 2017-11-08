
/*--------------------  CODE_ORIGIN @ 番茄  --------------------*/

#include <vector>

#include "global.h"
#include "advanced_CMD.h"
#include "FBric_operator.h"
#include "FA_tool.h"
#include "FA_itfX.h"

using namespace std;

//----- 全局变量区 -----//
struct timeval tv_begin,tv_end;

char *version = new char[10];
char *cr_month = new char[3];


//----- Main入口-----//
int main(int argc, char **argv, char *env[])
{
    if( FA_Read_Conf(version, cr_month) == -1 )
    {
        return -1;
    }

    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
    cout << "| |       FA_Automator System        | |" << endl;
    cout << "| |      >>>  番茄_summer  <<<       | |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
    cout << "| |        Version: " << version << "_LTU" << "         | |" << endl;
    cout << "| |        Current Month: " << cr_month << "         | |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;

    // advanced_CMD循环模式
    char advanced_CMD[MAX_COMMAND];
    int CMD_argc = 0;
    vector<string> CMD_argv;
    
    while(1)
    {
        cout << "CMD >>> ";
        cin.getline(advanced_CMD, MAX_COMMAND);

        // 判断是否输入空行
        if( CMD_Line_Parser(advanced_CMD, CMD_argc, CMD_argv) == -1 )
        {
            cout << "CMD is blank line !" << endl;
            cout << "----------------------------------------" << endl;
            
            continue;
        }
        
        // 判断是否输入撤销CMD
        if( CMD_argv.back().compare(CMD_CANCEL) == 0 )
        {
            cout << "CMD canceled !" << endl;
            cout << "----------------------------------------" << endl;
            
            continue;
        }

        /**************************************************/
        //   退出 FA_Auto系统
        //   CMD-> sd
        /**************************************************/
        if((CMD_argv.begin()->compare(CMD_SD) == 0)\
            && (CMD_argv.size() == 1))
        {
            cout << "----------------------------------------" << endl;
            cout << "|-----    FA_Automator SHUTDOWN   -----|" << endl;
            cout << "----------------------------------------" << endl;

            break;
        }

        /**************************************************/
        //   显示 .md文件
        //   CMD-> print ./NS.md
        /**************************************************/
        if((CMD_argv.begin()->compare(CMD_PRINT) == 0)\
            && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);

            cout << "----------------------------------------" << endl;
            FA_Print_File(CMD_argv.at(1).c_str());
            cout << "----------------------------------------" << endl;  
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   搜索 .md文件 单行
        //   CMD-> search ./NS.md temp
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_SEARCH) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);

            FA_Print_Line_Key(CMD_argv.at(1).c_str(), CMD_argv.at(2).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   修改 当月 支出
        //   CMD-> life 100 生活
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_LIFE) == 0)\
                && (CMD_argv.size() == 3))    
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_Modify_Month(cr_month, char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   更新 当月 收支
        //   CMD-> update month
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_UPDATE) == 0)\
                && (CMD_argv.at(1).compare(CMD_MONTH) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);
            
            FAitfX_Update_Month(cr_month);
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 当月 收支
        //   CMD-> check month
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_MONTH) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_Check_Month(cr_month);
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   更新 上月 收支
        //   CMD-> update month ex
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_UPDATE) == 0)\
                && (CMD_argv.at(1).compare(CMD_MONTH) == 0)\
                && (CMD_argv.at(2).compare(CMD_EX) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);
    
            FAitfX_Update_Month(GenPreMonth(cr_month).c_str());
    
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 上月 收支
        //   CMD-> check month ex
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_MONTH) == 0)\
                && (CMD_argv.at(2).compare(CMD_EX) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_Check_Month(GenPreMonth(cr_month).c_str());
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   增加 Books.M 支出
        //   CMD-> book 100 《史记》
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_BOOK) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);
    
            FAitfX_Modify_SubMonth("./Books.M.md", "Books.M", cr_month,\
                                   char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());
    
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;
             
            continue;
        }

        /**************************************************/
        //   增加 KEEP.M 支出
        //   CMD-> keep 100 云南白药
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_KEEP) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);
    
            FAitfX_Modify_SubMonth("./KEEP.M.md", "KEEP.M", cr_month,\
                                   char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());
    
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;
             
            continue;
        }

        /**************************************************/
        //   增加 TB.M 支出
        //   CMD-> tb 100 sth
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_TB) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);
    
            FAitfX_Modify_SubMonth("./TB.M.md", "TB.M", cr_month,\
                                   char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());
    
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;
             
            continue;
        }

        /**************************************************/
        //   增加 sa.M 支出
        //   CMD-> sa 100 红包
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_SA) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_Modify_SubMonth("./sa.M.md", "sa.M", cr_month,\
                                   char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;
         
            continue;
        }

        /**************************************************/
        //   更新 FA_TVT
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_UPDATE) == 0)\
                && (CMD_argv.at(1).compare(CMD_TVT) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_Update_TVT();

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 FA_TVT
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_TVT) == 0)\
                && (CMD_argv.size() == 2))     
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_Check_TVT();

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   增加 DK 支出
        //   CMD-> dk 5000 iPhone
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_DK) == 0)\
                && (CMD_argv.size() == 3))
        {
            if(char0check(CMD_argv.at(1).c_str()) != 0)
                continue;

            gettimeofday(&tv_begin, NULL);

            FAitfX_Modify_Title("./DK.md", "# Digital Kingdom", "## DK",\
                                char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 DK 支出
        //   CMD-> check dk
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_DK) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);
            
            FAitfX_Check_Title("./DK.md", "# Digital Kingdom", "## DK");
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   增加 NS 支出
        //   CMD-> ns 200 优衣库
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_NS) == 0)\
                && (CMD_argv.size() == 3))
        {
            if(char0check(CMD_argv.at(1).c_str()) != 0)
                continue;

            gettimeofday(&tv_begin, NULL);

            FAitfX_Modify_Title("./NS.md", "# New Style", "## NS",\
                                char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 NS 支出
        //   CMD-> check ns
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_NS) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);
            
            FAitfX_Check_Title("./NS.md", "# New Style", "## NS");
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   修改&更新 lottery.md 收支
        //   e.g.-> lottery -- 128 201711102
        //   e.g.-> lottery ++ 3000 201711102
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_LOTTERY) == 0)\
                && (CMD_argv.size() == 4))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_lottery(CMD_argv.at(1), char2int(CMD_argv.at(2).c_str()), CMD_argv.at(3).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 lottery 收支
        //   CMD-> check lottery
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_LOTTERY) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);
            
            FAitfX_Check_Title("./lottery.md", "# lottery", "## lottery");
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   balance 操作
        //   CMD-> balance ++ 100   // 广发银行 +100
        //   CMD-> balance -- 200   // 广发银行 -200
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_BALANCE) == 0)
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_Balance(char2int(CMD_argv.at(2).c_str()), CMD_argv.at(1).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   BackUp 全备份
        //   CMD-> bakup
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_BACKUP) == 0)\
                && (CMD_argv.size() == 1))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_BackUp("./FA_TVT.bak/");

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   TEST
        /**************************************************/
        else if( CMD_argv.begin()->compare(CMD_TEST) == 0 )
        {
            cout << "FA Analysis:" << endl;

            cout << "M09: ";
            for(int i = 0; i < 35; i++)
            {
                cout << "|";
            }
            cout << "3520" << endl;

            cout << "M10: ";
            for(int i = 0; i < 50; i++)
            {
                cout << "|";
            }
            cout << "5021" << endl;

            cout << "M11: ";
            for(int i = 0; i < 40; i++)
            {
                cout << "|";
            }
            cout << "4022" << endl;

            continue;
        }

        /**************************************************/
        //   CMD输入错误
        /**************************************************/
        else
        {
            cout << "----------------------------------------" << endl;
            cout << ">>>           Error Command          <<<" << endl;
            cout << "----------------------------------------" << endl;

            continue;
        }
    }

    return 0;
}


/*--------------------  CODE_END @ 番茄  --------------------*/


#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

namespace GFEM
{
    /**
     * @brief 材料属性定义类
     */
    class Material
    {
    protected:
        int materialId;
        std::string name;
        std::unordered_map<std::string, double> properties;

    public:
        Material(int id, const std::string &name) : materialId(id), name(name)
        {
        }

        /**
         * @brief 获取材料的某项属性值
         * @param key 指定的项的名称，如"conductivity"、"density"等
         * @return 属性值
         */
        double getProperty(const std::string &key) const
        {
            return properties.at(key);
        }

        /**
         * @brief 设置材料的某项属性值
         * @param key 指定的项的名称，如"conductivity"、"density"等
         * @param value 要设置的属性值
         */
        void setProperty(const std::string &key, double value)
        {
            properties[key] = value;
        }

        /**
         * @brief 获取材料的ID
         * @return int 材料的ID
         */
        int getId() const
        {
            return materialId;
        }

        /**
         * @brief 获取材料的名称
         * @return 材料的名称，如"Steel"
         */
        const std::string &getName() const
        {
            return name;
        }

        /**
         * @brief 输出材料的信息
         */
        void print() const
        {
            std::cout << "Material ID: " << materialId << std::endl;
            std::cout << "Material Name: " << name << std::endl;
            std::cout << "Material Properties:" << std::endl;
            for (const auto &[key, value] : properties)
            {
                std::cout << "    " << key << ": " << value << std::endl;
            }
        }
    };

}  // namespace GFEM

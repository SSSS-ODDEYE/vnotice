#pragma once

#ifndef _FACTORYMETHOD_HPP_
#define _FACTORYMETHOD_HPP_

#include <map>
#include <memory>
#include <string>

namespace ohtoai
{
    // Base class, product registration template interface class
    template <typename ProductType_t>
    class IProductRegistrar
    {
    public:
        virtual std::shared_ptr<ProductType_t> createProduct() = 0;
    protected:
        IProductRegistrar() = default;
        virtual ~IProductRegistrar() = default;
        IProductRegistrar(const IProductRegistrar&) = delete;
        IProductRegistrar& operator=(const IProductRegistrar&) = delete;
    };

    // Factory template class for getting and registering product objects
    template <typename ProductType_t>
    class ProductFactory
    {
    public:
        static ProductFactory<ProductType_t>& instance()
        {
            static ProductFactory<ProductType_t> instance;
            return instance;
        }

        // Product registration
        void registerProduct(IProductRegistrar<ProductType_t>* registrar, std::string name)
        {
            productRegistry_.emplace(name, registrar);
        }

        // Based on the name, get the corresponding specific product object
        std::shared_ptr<ProductType_t> product(std::string name)
        {
            if (productRegistry_.find(name) != productRegistry_.end())
                return productRegistry_.at(name)->createProduct();
            else
                return nullptr;
        }

    protected:
        ProductFactory() = default;
        ~ProductFactory() = default;
        ProductFactory(const ProductFactory&) = delete;
        ProductFactory& operator=(const ProductFactory&) = delete;

        // Save the registered products. Key: product name, value: product type
        std::map<std::string, IProductRegistrar<ProductType_t>*> productRegistry_;
    };

    // Product Registration template class for creating concrete products and registering products from the factory
    template <typename ProductType_t, typename ProductImpl_t, typename = typename std::enable_if<std::is_base_of<ProductType_t, ProductImpl_t>::value>::type>
    class ProductRegistrar : public IProductRegistrar<ProductType_t>
    {
    public:
        // The constructor, used to register the product to the factory, can only show the call
        explicit ProductRegistrar(std::string name)
        {
            // Register the product to the factory through the factory singleton
            ProductFactory<ProductType_t>::instance().registerProduct(this, name);
        }
        // Create a pointer to a concrete product object
        std::shared_ptr<ProductType_t> createProduct()
        {
            return std::make_shared<ProductImpl_t>();
        }
    };
}

#endif
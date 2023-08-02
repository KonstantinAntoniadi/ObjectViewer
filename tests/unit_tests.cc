#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include "../src/Command/Command.h"
#include "../src/FileReader/ObjectFileReader.h"
#include "../src/Object/Object.h"
#include "../src/Transformer/Transformer.h"

namespace object_viewer {
class ObjectViewerTest : public testing::Test {
 protected:
  std::string filepath_ = "tests/test_data/cube.obj";

  ObjectFileReader* reader_;
  Object* obj_;
  Transformer* transformer_;
  std::vector<double> etalon_values_;
  std::vector<double> result_values_;

  void SetUp() override {
    reader_ = new ObjectFileReader();
    obj_ = new Object();
    transformer_ = new Transformer();
  }

  void TearDown() override {
    etalon_values_.clear();
    result_values_.clear();
    delete reader_;
    delete obj_;
    delete transformer_;
  }
};

TEST_F(ObjectViewerTest, ExistingFile) {
  reader_->ReadFile(filepath_, obj_);
  EXPECT_EQ(obj_->vertexes_.size(), 8);
  EXPECT_EQ(obj_->facets_.size(), 72);
}

TEST_F(ObjectViewerTest, NonExistingFile) {
  reader_->ReadFile(filepath_, obj_);
  EXPECT_ANY_THROW(reader_->ReadFile("no_exits", obj_));
}

TEST_F(ObjectViewerTest, Scale) {
  reader_->ReadFile(filepath_, obj_);

  double scale = 10;
  for (auto& p : obj_->vertexes_) {
    for (int i = 0; i < 3; i++) {
      etalon_values_.push_back(p[i] * scale);
    }
  }

  transformer_->SetCommand(std::make_shared<Scale>(scale));
  transformer_->Transform(obj_);

  for (auto& p : obj_->vertexes_) {
    for (int i = 0; i < 3; i++) {
      result_values_.push_back(p[i]);
    }
  }

  for (size_t i = 0; i < result_values_.size(); i++) {
    EXPECT_DOUBLE_EQ(etalon_values_[i], result_values_[i]);
  }
}

TEST_F(ObjectViewerTest, Move) {
  reader_->ReadFile(filepath_, obj_);

  double x = 5.5, y = 7.1, z = 21.1;
  for (auto& p : obj_->vertexes_) {
    etalon_values_.push_back(p.x + x);
    etalon_values_.push_back(p.y + y);
    etalon_values_.push_back(p.z + z);
  }

  transformer_->SetCommand(std::make_shared<Move>(x, y, z));
  transformer_->Transform(obj_);

  for (auto& p : obj_->vertexes_) {
    result_values_.push_back(p.x);
    result_values_.push_back(p.y);
    result_values_.push_back(p.z);
  }

  for (size_t i = 0; i < result_values_.size(); i++) {
    EXPECT_DOUBLE_EQ(etalon_values_[i], result_values_[i]);
  }
}

TEST_F(ObjectViewerTest, Rotate) {
  reader_->ReadFile(filepath_, obj_);

  double x_angel = 360, y_angel = 360, z_angel = 360;
  for (auto& p : obj_->vertexes_) {
    etalon_values_.push_back(p.x);
    etalon_values_.push_back(p.y);
    etalon_values_.push_back(p.z);
  }

  transformer_->SetCommand(std::make_shared<Rotate>(x_angel, y_angel, z_angel));
  transformer_->Transform(obj_);

  for (auto& p : obj_->vertexes_) {
    result_values_.push_back(p.x);
    result_values_.push_back(p.y);
    result_values_.push_back(p.z);
  }

  for (size_t i = 0; i < result_values_.size(); i++) {
    EXPECT_DOUBLE_EQ(etalon_values_[i], result_values_[i]);
  }
}

}  // namespace object_viewer

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

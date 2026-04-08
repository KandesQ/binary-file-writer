#include <iostream>

#include "src/file/BinaryFileWriter.h"
#include "src/file/TextFileReader.h"
#include "src/ListNode.h"

const std::string IN_FILENAME = "inlet.in";
const std::string OUT_FILENAME = "outlet.out";

int main() {
    TextFileReader reader(IN_FILENAME);

    const List::ListInfo list_info = reader.read_list();

    if (!list_info.head) {
        std::cout << "ListInfo is empty" << std::endl;
        return 0;
    }

    List::ListNode* head{list_info.head};

    // Test: shows list
    List::print_list(head);

    BinaryFileWriter writer(OUT_FILENAME);
    writer.write_list(head, list_info.node_index_to_rand_node_index);

    List::clear_list(head);
    return 0;
}
